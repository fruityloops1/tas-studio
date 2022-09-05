#include "al/LiveActor/LiveActor.h"
#include "al/actor/ActorInitInfo.h"
#include "al/camera/CameraDirector.h"
#include "al/camera/CameraPoser.h"
#include "al/nerve/Nerve.h"
#include "al/resource/Resource.h"
#include "al/scene/Scene.h"
#include "al/scene/SceneInitInfo.h"
#include "al/sensor/HitSensorKeeper.h"
#include "al/sequence/Sequence.h"
#include "al/util.hpp"
#include "fl/OutPacket.h"
#include "fl/Server.h"
#include "fl/TasHeap.h"
#include "fl/TasHooks.h"
#include "fl/TasPackets.h"
#include "fl/TasServer.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/StageScene/StageScene.h"
#include "gfx/seadCamera.h"
#include "heap/seadHeapMgr.h"
#include "lib.hpp"
#include "math/seadMatrix.h"
#include "math/seadQuat.h"
#include "math/seadVector.h"
#include "nn/os.h"
#include "nn/socket.h"
#include "patch/code_patcher.hpp"
#include <cstdlib>
#include <cstring>
#include <sead/container/seadPtrArray.h>

void hakoniwaSequenceUpdateHook(HakoniwaSequence* dis)
{
    dis->al::Sequence::update();
    al::Scene* scene = dis->getCurrentScene();

    fl::tryCreateTasHeap();
    fl::TasServer::instance().tryStart();
}

static sead::Quatf getActorRotate(al::LiveActor* actor)
{
    const sead::Quatf* quat = al::getQuatPtr(actor);
    const sead::Vector3f* rotate = al::getRotatePtr(actor);

    if (quat) {
        bool quatContains = quat->x != 0 || quat->y != 0 || quat->z != 0 || quat->w != 1;
        if(quatContains)
            return *quat;
    }
    if (rotate && *rotate != sead::Vector3f::zero) {
        sead::Vector3f rot = *rotate;
        sead::Quatf q{};
        rot *= sead::numbers::pi / 180.0;
        q.setRPY(rotate->x, rotate->y, rotate->z);
        return q;
    }
    return sead::Quatf::unit;
}

static al::LiveActor** collisionActors = nullptr;
static int collisionActorAmount = 0;
static bool aliveDataBuffer[580] { 0 };
static fl::packets::ActorUpdate::Entry actorUpdateEntryBuffer[32] {};

void stageSceneControlHook()
{
    __asm("mov x19, x0");

    StageScene* stageScene;
    __asm("mov %[result], x0"
          : [result] "=r"(stageScene));

    sead::LookAtCamera* camera = al::getLookAtCamera(stageScene, 0);
    {
        fl::packets::CameraInfo packet(camera->getPos(), camera->getAt(), camera->getUp(), 65);
        fl::TasServer::instance().sendPacket(packet);
    }

    static int interval = 0;
    interval++;
    if (interval == 3) {
        int aliveAmount = 0;
        int actorUpdateIndex = 0;

        for (int i = 0; i < collisionActorAmount; i++) {
            al::LiveActor* actor = collisionActors[i];
            bool process = al::isAlive(actor) && !al::isClipped(actor);
            aliveDataBuffer[i] = process;
            if (process) {
                aliveAmount++;
                actorUpdateEntryBuffer[actorUpdateIndex] = { u32(i), al::getTrans(actor), al::getScale(actor), getActorRotate(actor) };
                actorUpdateIndex++;

                if (actorUpdateIndex >= 32) {
                    fl::packets::ActorUpdate packet(actorUpdateEntryBuffer, actorUpdateIndex);
                    fl::TasServer::instance().sendPacket(packet);
                    actorUpdateIndex = 0;
                }
            }
        }

        if (actorUpdateIndex != 0) {
            fl::packets::ActorUpdate packet(actorUpdateEntryBuffer, actorUpdateIndex);
            fl::TasServer::instance().sendPacket(packet);
            actorUpdateIndex = 0;
        }

        fl::packets::ActorAliveStatus packet(aliveDataBuffer, collisionActorAmount);
        fl::TasServer::instance().sendPacket(packet);

        interval = 0;
    }

    __asm("mov x0, %[input]"
          : [input] "=r"(stageScene));
}

bool playerControlHook(PlayerActorHakoniwa* player, const al::Nerve* nerve)
{
    fl::packets::PlayerInfo::Entry playerInfoSensorEntryBuffer[24];
    int i = 0;
    playerInfoSensorEntryBuffer[0].pos = al::getTrans(player);
    playerInfoSensorEntryBuffer[0].radius = player->mPlayerCollider->getColliderRadius();
    for (al::HitSensor& sensor : player->mHitSensorKeeper->mHitSensors) {
        playerInfoSensorEntryBuffer[i + 1].pos = al::getSensorPos(&sensor);
        playerInfoSensorEntryBuffer[i + 1].radius = al::getSensorRadius(&sensor);
        i++;
    }
    fl::packets::PlayerInfo packet(al::getTrans(player), al::getTrans(player->mHackCap), playerInfoSensorEntryBuffer, i + 1);
    fl::TasServer::instance().sendPacket(packet);
    return al::isNerve(player, nerve);
}

HOOK_DEFINE_TRAMPOLINE(ActorInitHook) { static void Callback(al::LiveActor * actor, al::Resource * resource, const sead::SafeString& kclName, al::HitSensor* collisionSensor, const sead::Matrix34f* mtx, const char* str); };

void ActorInitHook::Callback(al::LiveActor* actor, al::Resource* resource, const sead::SafeString& kclName, al::HitSensor* collisionSensor, const sead::Matrix34f* mtx, const char* str)
{
    Orig(actor, resource, kclName, collisionSensor, mtx, str);
    fl::packets::ActorInit packet(collisionActorAmount, al::getTrans(actor), al::getScale(actor), getActorRotate(actor), resource->getArchiveName(), kclName.cstr());
    fl::TasServer::instance().sendPacket(packet);
    collisionActors[collisionActorAmount] = actor;
    collisionActorAmount++;
}

HOOK_DEFINE_TRAMPOLINE(StageSceneInitHook) { static void Callback(StageScene * scene, const al::SceneInitInfo& info); };
void StageSceneInitHook::Callback(StageScene* scene, const al::SceneInitInfo& info)
{
    if (collisionActors == nullptr) {
        sead::ScopedCurrentHeapSetter setter(fl::getTasHeap());
        collisionActors = new al::LiveActor*[580];
    }

    collisionActorAmount = 0;
    fl::packets::SceneInit packet;
    fl::TasServer::instance().sendPacket(packet);
    Orig(scene, info);
}

PATCH_DEFINE_ASM_SIMPLE(Ret, "ret");
PATCH_DEFINE_ASM_SIMPLE(WorldResourceLoader1, R"(
    mov w0, #1
    ret
)");

extern "C" void exl_main(void* x0, void* x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    using namespace exl::patch::inst;
    using namespace exl::patch;

    CodePatcher(0x0050f04c).BranchLinkInst((void*)&hakoniwaSequenceUpdateHook);
    CodePatcher(0x00420780).BranchLinkInst((void*)&playerControlHook);
    CodePatcher(0x004cc360).BranchLinkInst((void*)&stageSceneControlHook);

    {
        CodePatcher a(0x00514810);
        for (int i = 0; i < 10; i++)
            a.WriteInst(Nop());
    }
    for (uintptr_t offset : { 0x00514710, 0x00514700, 0x00514540, 0x00514050 })
        Ret::InstallAtOffset(offset);
    WorldResourceLoader1::InstallAtOffset(0x005146f8);

    ActorInitHook::InstallAtOffset(0x008db2b4);
    StageSceneInitHook::InstallAtOffset(0x004c861c);

    fl::initTasInputHooks();
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    __asm("svc #0x26");
    EXL_ABORT(0x420);
}

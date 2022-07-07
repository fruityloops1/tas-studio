#include "al/LiveActor/LiveActor.h"
#include "al/actor/ActorInitInfo.h"
#include "al/camera/CameraDirector.h"
#include "al/camera/CameraPoser.h"
#include "al/nerve/Nerve.h"
#include "al/scene/Scene.h"
#include "al/sequence/Sequence.h"
#include "al/util.hpp"
#include "fl/OutPacket.h"
#include "fl/Server.h"
#include "fl/TasHooks.h"
#include "fl/TasServer.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/StageScene/StageScene.h"
#include "gfx/seadCamera.h"
#include "lib.hpp"
#include "math/seadVector.h"
#include "nn/socket.h"
#include "patch/code_patcher.hpp"

class InitActor : public fl::OutPacket {
    sead::Vector3f mPos;

public:
    InitActor(const sead::Vector3f& pos)
        : OutPacket(1)
        , mPos(pos)
    {
    }
    size_t calcSize() override { return sizeof(sead::Vector3f); }
    void construct(u8* out) override { *(sead::Vector3f*)out = mPos; }
};

void hakoniwaSequenceUpdateHook(HakoniwaSequence* dis)
{
    ((al::Sequence*)dis)->update();
    al::Scene* scene = dis->getCurrentScene();

    fl::TasServer::instance().tryStart();
}

class CameraInfo : public fl::OutPacket {
    struct {
        sead::Vector3f pos;
        sead::Vector3f at;
        sead::Vector3f up;
        float fovy;
    } mData;

public:
    CameraInfo(const sead::Vector3f& pos, const sead::Vector3f& at, const sead::Vector3f& up, float fovy)
        : OutPacket(3)
    {
        mData.pos = pos;
        mData.at = at;
        mData.up = up;
        mData.fovy = fovy;
    }

    size_t calcSize() override { return sizeof(mData); }
    void construct(u8* out) override
    {
        *(typeof(mData)*)out = mData;
    }
};

void stageSceneControlHook()
{
    __asm("mov x19, x0");

    StageScene* stageScene;
    __asm("mov %[result], x0"
          : [result] "=r"(stageScene));

    sead::LookAtCamera* camera = al::getLookAtCamera(stageScene, 0);
    {
        CameraInfo packet(camera->getPos(), camera->getAt(), camera->getUp(), 65);
        fl::TasServer::instance().sendPacket(packet);
    }

    __asm("mov x0, %[input]"
          : [input] "=r"(stageScene));
}

class PlayerInfo : public fl::OutPacket {

    sead::Vector3f mTrans;

public:
    PlayerInfo(const sead::Vector3f& trans)
        : OutPacket(2)
        , mTrans(trans)
    {
    }
    size_t calcSize() override { return sizeof(mTrans); }
    void construct(u8* out) override { *(sead::Vector3f*)out = mTrans; }
};

bool playerControlHook(PlayerActorHakoniwa* player, const al::Nerve* nerve)
{
    PlayerInfo packet(al::getTrans(player));
    fl::TasServer::instance().sendPacket(packet);
    return al::isNerve(player, nerve);
}

class ActorInit : public fl::OutPacket {
    struct {
        uintptr_t actorPtr;
        sead::Vector3f initTrans;
        sead::Vector3f initScale;
    } mFixed;
    const char* mObjectName = nullptr;

public:
    ActorInit(al::LiveActor* actor, const sead::Vector3f& trans, const sead::Vector3f& scale, const char* objectName)
        : OutPacket(4)
        , mObjectName(objectName)
    {
        mFixed.actorPtr = (uintptr_t)actor;
        mFixed.initTrans = trans;
        mFixed.initScale = scale;
    }
    size_t calcSize() override
    {
        return sizeof(mFixed) + (mObjectName == nullptr ? 0 : strlen(mObjectName)) + 1;
    }
    void construct(u8* out) override
    {
        *(typeof(mFixed)*)out = mFixed;
        if (mObjectName != nullptr)
            strcpy((char*)&out[sizeof(mFixed)], mObjectName);
        else
            out[sizeof(mFixed)] = '\0';
    }
};

void actorInitHook(al::LiveActor* actor, const al::ActorInitInfo& info)
{
    actor->init(info);
    const char* name = nullptr;
    if (!al::tryGetObjectName(&name, info))
        name = nullptr;
    ActorInit packet(actor, al::getTrans(actor), al::getScale(actor), name);
    fl::TasServer::instance().sendPacket(packet);
}

extern "C" void exl_main(void* x0, void* x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    exl::patch::CodePatcher(0x0050f04c).BranchLinkInst((void*)&hakoniwaSequenceUpdateHook);
    exl::patch::CodePatcher(0x00420780).BranchLinkInst((void*)&playerControlHook);
    exl::patch::CodePatcher(0x004cc360).BranchLinkInst((void*)&stageSceneControlHook);

    exl::patch::CodePatcher(0x008ddc38).BranchLinkInst((void*)&actorInitHook);
    exl::patch::CodePatcher(0x008ddc9c).BranchLinkInst((void*)&actorInitHook);
    exl::patch::CodePatcher(0x008ddb88).BranchInst((void*)&actorInitHook);
    exl::patch::CodePatcher(0x008ddbd4).BranchLinkInst((void*)&actorInitHook);
    exl::patch::CodePatcher(0x008dd994).BranchLinkInst((void*)&actorInitHook);

    fl::initTasInputHooks();
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}
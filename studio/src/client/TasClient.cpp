#include "client/TasClient.h"
#include "file/KCollision.h"
#include "nlib/util.h"
#include "oead/sarc.h"
#include "oead/yaz0.h"
#include "types.h"
#include "ui/Scene.h"
#include <cstdio>
#include <filesystem>

namespace fl {

void TasClient::receiveLog(u8* data, size_t len)
{
    printf("%s\n", data);
}

void TasClient::receivePlayerInfo(u8* data, size_t len)
{
    auto& scene = Scene::instance();
    scene.playerPos = (*(Vector3f*)data) / 100;
    scene.cappyPos = (*(Vector3f*)&data[sizeof(Vector3f)]) / 100;

    u32 sensorAmount = (len - sizeof(Vector3f) * 2) / sizeof(Scene::SensorInfo);
    Scene::SensorInfo* sensors = (Scene::SensorInfo*)&data[sizeof(Vector3f) * 2];
    if (scene.playerSensors.empty())
        for (int i = 0; i < sensorAmount; i++)
            scene.playerSensors.push_back({ sensors[i].radius, sensors[i].pos / 100 });
    else
        for (int i = 0; i < sensorAmount; i++)
            scene.playerSensors[i] = { sensors[i].radius, sensors[i].pos / 100 };
}

void TasClient::receiveCameraInfo(u8* data, size_t len)
{
    auto& visual = Scene::instance();
    visual.cameraInfo = *(Scene::CameraInfo*)data;
    visual.cameraInfo.pos /= 100;
    visual.cameraInfo.at /= 100;
}

void TasClient::receiveActorInit(u8* data, size_t len)
{
    auto& scene = Scene::instance();

    struct {
        u32 actorIndex;
        fl::Vector3f initTrans;
        fl::Vector3f initScale;
        fl::Quatf initRotate;
    } fixed = *(typeof(fixed)*)data;

    const char* archiveName = (const char*)&data[sizeof(fixed)];
    const char* kclName = (const char*)&data[sizeof(fixed) + strlen(archiveName) + 1];
    printf("%s.kcl\n", kclName);
    scene.actors.push_back(new Scene::Actor(archiveName, kclName));
    Scene::Actor& actor = *scene.actors.back();
    actor.trans = fixed.initTrans;
    actor.scale = fixed.initScale;
    actor.rotate = fixed.initRotate;
    actor.index = fixed.actorIndex;
    actor.kcl.initPending = true;
}

void TasClient::receiveActorAliveStatus(u8* data, size_t len)
{
    u32 amount = *(u32*)data;
    bool* bools = (bool*)&data[4];

    auto& scene = Scene::instance();
    for (Scene::Actor* actor : scene.actors) {
        actor->isAlive = bools[actor->index];
    }
}

void TasClient::receiveActorUpdate(u8* data, size_t len)
{
    u32 amount = *(u32*)data;
    struct Entry {
        u32 index;
        fl::Vector3f pos;
        fl::Vector3f scale;
        fl::Quatf rotate;
    }* entries = (Entry*)&data[4];

    auto& scene = Scene::instance();

    for (int i = 0; i < amount; i++) {
        Entry& entry = entries[i];
        if (entry.index >= scene.actors.size()) {
            printf("Error: index of entry to update out of bounds (%i / %li)\n", entry.index, scene.actors.size());
            continue;
        }

        Scene::Actor* actor = scene.actors[entry.index];
        if((actor->trans != entry.pos) || (actor->scale != entry.scale) || (actor->rotate != entry.rotate))
            printf("updating %s: ", actor->getName());
        if(actor->trans != entry.pos)
            printf("trans: (x: %f, y: %f, z: %f) to (x: %f, y: %f, z: %f), ", actor->trans.x, actor->trans.y, actor->trans.z, entry.pos.x, entry.pos.y, entry.pos.z);
        if(actor->scale != entry.scale)
            printf("scale: (x: %f, y: %f, z: %f) to (x: %f, y: %f, z: %f), ", actor->scale.x, actor->scale.y, actor->scale.z, entry.scale.x, entry.scale.y, entry.scale.z);
        if(actor->rotate != entry.rotate)
            printf("rotate: (x: %f, y: %f, z: %f) to (x: %f, y: %f, z: %f), ", actor->rotate.x, actor->rotate.y, actor->rotate.z, entry.rotate.x, entry.rotate.y, entry.rotate.z);
        
        if((actor->trans != entry.pos) || (actor->scale != entry.scale) || (actor->rotate != entry.rotate))
            printf("\n");
        actor->trans = entry.pos;
        actor->scale = entry.scale;
        actor->rotate = entry.rotate;
    }
}

void TasClient::receiveSceneInit(u8* data, size_t len)
{
    auto& scene = Scene::instance();
    for (Scene::Actor* actor : scene.actors)
        delete actor;
    scene.actors.clear();
}

} // namespace fl
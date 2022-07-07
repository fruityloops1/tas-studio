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
    Scene::instance().playerPos = (*(Vector3f*)data) / 100;
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
    auto& visual = Scene::instance();

    struct {
        uintptr_t actorPtr;
        fl::Vector3f initTrans;
        fl::Vector3f initScale;
    } fixed = *(typeof(fixed)*)data;

    const char* name = (const char*)&data[sizeof(fixed)];
    visual.actors.push_back(new Scene::Actor(name));
    Scene::Actor& actor = *visual.actors.back();
    actor.trans = fixed.initTrans;
    actor.scale = fixed.initScale;
    actor.unique = fixed.actorPtr;

    std::string szsPath = nlib::util::format("res/ObjectData/%s.szs", actor.getName());

    if (std::filesystem::exists(szsPath)) {
        std::vector<u8> szsData = nlib::util::readFile<u8>(szsPath);
        std::vector<u8> sarcData = oead::yaz0::Decompress(szsData);
        oead::Sarc sarc(sarcData);
        for (const auto& file : sarc.GetFiles()) {
            if (file.name.ends_with(".kcl")) {
                KCL kcl(file.data);

                std::string objName = nlib::util::format("%s.obj", file.name.data());
                std::string mtlName = nlib::util::format("%s.mtl", file.name.data());
                std::string objStr = nlib::util::format("mtllib %s\n", mtlName.c_str());
                objStr.append(kcl.toObj());
                std::string mtlStr = kcl.toMtl();
                std::vector<u8> obj(objStr.begin(), objStr.end());
                std::vector<u8> mtl(mtlStr.begin(), mtlStr.end());

                nlib::util::writeFile(objName, std::span<const u8>(obj));
                printf("%s\n", objName.c_str());
                nlib::util::writeFile(mtlName, std::span<const u8>(mtl));
                actor.kcl.model = LoadModel(objName.c_str());

                for (int i = 0; i < actor.kcl.model.materialCount; i++) {
                    actor.kcl.model.materials[i].maps->color = WHITE;
                    actor.kcl.model.materials[i].shader = visual.checkerShader;
                }

                actor.kcl.valid = true;
                // std::filesystem::remove(objName);
                // std::filesystem::remove(mtlName);
            }
        }
    }
}

} // namespace fl
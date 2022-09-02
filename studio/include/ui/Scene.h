#pragma once

#include "raylib.h"
#include "types.h"
#include <cstring>
#include <unordered_map>
#include <vector>

namespace fl {

struct Scene {
    static Scene& instance();

    Vector3f cappyPos;
    Vector3f playerPos;
    struct SensorInfo {
        float radius;
        fl::Vector3f pos;
    };
    std::vector<SensorInfo> playerSensors;

    Shader checkerShader;

    struct CameraInfo {
        fl::Vector3f pos;
        fl::Vector3f at;
        fl::Vector3f up;
        float fovy;
    } cameraInfo;

    class Actor {
        const char* const mArchiveName = nullptr;
        const char* mKCLName = nullptr;

    public:
        u32 index;
        fl::Vector3f trans;
        fl::Vector3f scale;
        fl::Vector3f rotate;
        bool isAlive = false;

        struct {
            ::Model model;
            bool valid = false;
            bool initPending = false;
        } kcl;

        Actor(const char* name, const char* kclName = nullptr)
            : mArchiveName(strdup(name))
        {
            if (kclName)
                mKCLName = strdup(kclName);
        }
        ~Actor()
        {
            free((void*)mArchiveName);
            if (mKCLName)
                free((void*)mKCLName);
            if (kcl.valid)
                UnloadModel(kcl.model);
        }
        const char* const getName() const { return mArchiveName; }
        const char* const getKCLName() const { return mKCLName; }
    };
    std::vector<Actor*> actors;
};

} // namespace fl
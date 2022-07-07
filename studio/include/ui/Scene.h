#pragma once

#include "raylib.h"
#include "types.h"
#include <cstring>
#include <unordered_map>
#include <vector>

namespace fl {

struct Scene {
    static Scene& instance();

    Vector3f playerPos;

    Shader checkerShader;

    struct CameraInfo {
        fl::Vector3f pos;
        fl::Vector3f at;
        fl::Vector3f up;
        float fovy;
    } cameraInfo;

    class Actor {
        const char* const mObjectName = nullptr;

    public:
        uintptr_t unique;
        fl::Vector3f trans;
        fl::Vector3f scale;

        struct {
            ::Model model;
            bool valid = false;
        } kcl;

        Actor(const char* name)
            : mObjectName(strdup(name))
        {
        }
        ~Actor()
        {
            free((void*)mObjectName);
            if (kcl.valid)
                UnloadModel(kcl.model);
        }
        const char* const getName() const { return mObjectName; }
    };
    std::vector<Actor*> actors;
};

} // namespace fl
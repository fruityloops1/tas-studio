#pragma once

#include "al/camera/CameraDirector.h"
#include "al/message/MessageSystem.h"
#include "al/scene/SceneObjHolder.h"
#include "game/System/GameSystemInfo.h"

namespace al {
class LayoutSceneInfo {
public:
    void* gap;
    al::CameraDirector* mCameraDirector;
    void* mPadRumbleDirector;
    al::SceneObjHolder* mSceneObjHolder;
    al::MessageSystem* mMessageSystem;
    al::GamePadSystem* mGamepadSystem;
};
}

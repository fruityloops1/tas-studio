#pragma once

#include "raylib.h"
#include "types.h"

namespace fl {

class Camera {
    ::Camera3D mRlCamera;
    fl::Vector3f mPosition { 0, 10, 10 };
    fl::Vector3f mUp { 0, 1, 0 };
    fl::Vector3f mDirection { 0, 0, -1 };
    float mFovy = 65;

    fl::Vector2f mCameraMoveVel { 0, 0 };
    float mWheelMoveVel = 0;

    void convert();

public:
    Camera();
    void update();

    explicit operator Camera3D&() { return mRlCamera; }
    inline Vector3f getDirection() { return mDirection.normalize(); }
};

} // namespace fl
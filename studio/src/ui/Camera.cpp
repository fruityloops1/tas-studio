#include "ui/Camera.h"
#include "raylib.h"
#include "types.h"
#include <cmath>

namespace fl {

Camera::Camera()
{
    mRlCamera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(mRlCamera, CAMERA_CUSTOM);
}

void Camera::convert()
{
    mRlCamera.position = { mPosition.x, mPosition.y, mPosition.z };
    mRlCamera.up = { mUp.x, mUp.y, mUp.z };
    fl::Vector3f target = mPosition + mDirection;
    mRlCamera.target = { target.x, target.y, target.z };
    mRlCamera.fovy = mFovy;
}

Vector3f rotateVectorY(const Vector3f& vector, float angle)
{
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    return {
        vector.x * cosAngle - vector.z * sinAngle,
        vector.y,
        vector.x * sinAngle + vector.z * cosAngle
    };
}

Vector3f rotateVectorX(const Vector3f& vector, float angle)
{
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    return {
        vector.x,
        vector.y * cosAngle - vector.z * sinAngle,
        vector.y * sinAngle + vector.z * cosAngle
    };
}

Vector3f rotateVectorZ(const Vector3f& vector, float angle)
{
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    return {
        vector.x * cosAngle - vector.y * sinAngle,
        vector.x * sinAngle + vector.y * cosAngle,
        vector.z
    };
}

void Camera::update()
{
    convert();

    ::Vector2 pos = GetMouseDelta();
    Vector2f delta { pos.x, pos.y };

    mWheelMoveVel += GetMouseWheelMove();
    if ((delta.x != 0 || delta.y != 0) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        mCameraMoveVel += delta * .0006f;

    mDirection = rotateVectorY(mDirection, mCameraMoveVel.x);
    mDirection.y += -mCameraMoveVel.y;
    mDirection = mDirection.normalize();

    if (mWheelMoveVel != 0) {
        float speed = IsKeyDown(KEY_LEFT_SHIFT) ? 4 : 2;
        float degree = (GetMouseX() + (float)GetScreenWidth() / 2) / GetScreenWidth() - 1;
        Vector3f dir = rotateVectorY(mDirection, degree);
        dir.y += -(GetMouseY() / (float)GetScreenHeight() - 0.5);
        mPosition += dir * (mWheelMoveVel * .25) * speed;
        // mPosition += mDirection;
    }

    mWheelMoveVel /= 1.4;
    mCameraMoveVel /= 1.4;
}

} // namespace fl
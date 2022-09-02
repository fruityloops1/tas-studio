#pragma once

#include "al/collision/KCollisionServer.h"
#include "al/sensor/HitSensor.h"
#include "math/seadMatrix.h"
#include "math/seadVector.h"

namespace al {

class CollisionParts // size==0x170|368
{
public:
    void* unkPtr1;
    void* unkPtr2;
    unsigned char unk1[0x8];
    void* unkPtr3;
    sead::Matrix34f* mSomeMatrix1; // 0x20
    sead::Matrix34f* mSomeMatrix2; // 0x28
    unsigned char unk2[0x28];
    sead::Matrix34f mSomeMatrix3; // 0x58
    unsigned char unk3[0xA8];
    al::KCollisionServer* mKCollisionServer; // 0x130
    al::HitSensor* mHitSensor; // 0x138
    const char* mSomeString1; // maybe relating to the hitsensor name or smth
    const char* mSomeString2; // maybe relating to the hitsensor name or smth
    sead::Vector3f mScaleVector; // 0x150
    unsigned char unk5[0x10];
};

}
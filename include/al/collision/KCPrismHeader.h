#pragma once

#include "al/collision/KCPrismData.h"
#include "container/seadPtrArray.h"
#include "container/seadSafeArray.h"
#include "math/seadVector.h"

namespace al {

class KCPrismHeader // size==0x4C|76
{
public:
    sead::PtrArray<sead::Vector3f>* mVertices;
    // sead::Vector3f* mVertices; // 0x00
    al::KCPrismData* mPrismData; // 0x08
    unsigned char unk1[0x38];
    // float mSomeFloat; // 0x48
};

}
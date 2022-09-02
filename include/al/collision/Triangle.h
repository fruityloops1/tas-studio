#pragma once

#include "al/collision/CollisionParts.h"
#include "al/collision/KCPrismData.h"
#include "al/collision/KCPrismHeader.h"
#include "math/seadVector.h"
#include "sead/math/seadQuat.h"

namespace al {

class Triangle // size==0x88|136
{
public:
    Triangle();
    Triangle(al::CollisionParts const&, al::KCPrismData const*, al::KCPrismHeader const*);
    void fillData(al::CollisionParts const&, al::KCPrismData const*, al::KCPrismHeader const*);
    void fill(sead::Vector3f const&, sead::Vector3f const&, sead::Vector3f const&);
    al::LiveActor* getHostActor() const;
    bool isHostMoved() const;
    bool isValid() const;
    sead::Vector3f* getNormal(int) const;
    sead::Vector3f* getFaceNormal() const;
    sead::Vector3f* getEdgeNormal(int) const;
    sead::Vector3f getPos(int) const;
    void calcCenterPos(sead::Vector3f*) const;
    sead::Vector3f* calcAndGetNormal(int);
    sead::Vector3f* calcAndGetFaceNormal();
    sead::Vector3f* calcAndGetEdgeNormal(int);
    sead::Vector3f* calcAndGetPos(int);
    void getLocalPos(sead::Vector3f*, int) const;
    sead::Vector3f* calcForceMovePower(sead::Vector3f*, sead::Vector3f const&) const;
    void calcForceRotatePower(sead::Quatf*) const;
    void* getAttributes(al::ByamlIter*) const;
    void* getSensor() const;
    void* getBaseMtx() const;
    void* getBaseInvMtx() const;
    void* getPrevBaseMtx() const;

    al::CollisionParts* mCollisionParts;
    al::KCPrismData* mKCPrismData;
    al::KCPrismHeader* mKCPrismHeader;
    sead::Vector3f mFaceNormal;
    sead::Vector3f mEdgeNormals[3];
    sead::Vector3f mVertices[3];
    unsigned char unk2[0x1C];
};

}
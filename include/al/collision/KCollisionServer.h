#pragma once

#include "al/byaml/ByamlIter.h"
#include "al/collision/KCHitInfo.h"
#include "al/collision/KCPrismData.h"
#include "al/collision/KCPrismHeader.h"
#include "container/seadPtrArray.h"
#include "math/seadVector.h"
#include "sead/container/seadRingBuffer.h"
#include "sead/thread/seadDelegateThread.h"
#include "types.h"

namespace al {

class KCollisionServer // size==0x50|80
{
public:
    KCollisionServer();
    void initKCollisionServer(void* mKclData, const void* mAttributeByml); // likely return type
    void setData(void* mKclData); // likely return type
    void* getInnerKcl(int) const; // unknown return type
    int getNumInnerKcl() const; // likely return type
    al::KCPrismHeader* getV1Header(int) const; // likely return type
    float calcFarthestVertexDistance(); // likely return type
    int getTriangleNum(al::KCPrismHeader const*) const; // likely return type
    al::KCPrismData* getPrismData(unsigned int index, al::KCPrismHeader const*) const; // likely return type
    bool isNearParallelNormal(al::KCPrismData const*, al::KCPrismHeader const*) const; // likely return type
    bool isNanPrism(al::KCPrismData const*, al::KCPrismHeader const*) const; // likely return type
    void calcPosLocal(sead::Vector3f*, al::KCPrismData const*, int, al::KCPrismHeader const*) const; // unknown return type
    void getMinMax(sead::Vector3f*, sead::Vector3f*) const; // unknown return type
    void getAreaSpaceSize(sead::Vector3f*, al::KCPrismHeader const*) const; // unknown return type
    void getAreaSpaceSize(int*, int*, int*, al::KCPrismHeader const*) const; // unknown return type
    void getAreaSpaceSize(sead::Vector3<unsigned int>*, al::KCPrismHeader const*) const; // unknown return type
    KCPrismData* checkPoint(sead::Vector3f*, float, float*); // unknown return type
    void searchBlock(int*, sead::Vector3<unsigned int> const&, al::KCPrismHeader const*) const; // unknown return type
    uint checkSphere(sead::Vector3f const*, float, float, unsigned int, sead::FixedRingBuffer<al::KCHitInfo, 512>*); // unknown return type
    void outCheckAndCalcArea(sead::Vector3<unsigned int>*, sead::Vector3<unsigned int>*, sead::Vector3f const&, sead::Vector3f const&, al::KCPrismHeader const*) const; // unknown return type
    void KCHitSphere(al::KCPrismData const*, al::KCPrismHeader const*, sead::Vector3f const*, float, float, float*, unsigned char*); // unknown return type
    KCPrismData* checkArrow(sead::Vector3f const&, sead::Vector3f const&, sead::FixedRingBuffer<al::KCHitInfo, 512>*, unsigned int*, unsigned int) const; // unknown return type
    void objectSpaceToAreaOffsetSpaceV3f(sead::Vector3f*, sead::Vector3f const&, al::KCPrismHeader const*) const; // unknown return type
    bool isInsideMinMaxInAreaOffsetSpace(sead::Vector3<unsigned int> const&, al::KCPrismHeader const*) const; // likely return type
    void KCHitArrow(al::KCPrismData const*, al::KCPrismHeader const*, sead::Vector3f const&, sead::Vector3f const&, float*, unsigned char*) const; // unknown return type
    uint checkSphereForPlayer(sead::Vector3f const*, float, float, unsigned int, sead::FixedRingBuffer<al::KCHitInfo, 512>*); // unknown return type
    void KCHitSphereForPlayer(al::KCPrismData const*, al::KCPrismHeader const*, sead::Vector3f const*, float, float, float*, unsigned char*); // unknown return type
    uint checkDisk(sead::Vector3f const*, float, float, sead::Vector3f const&, float, unsigned int, sead::FixedRingBuffer<al::KCHitInfo, 512>*); // unknown return type
    void KCHitDisk(al::KCPrismData const*, al::KCPrismHeader const*, sead::Vector3f const*, float, float, float, sead::Vector3f const&, float*, unsigned char*); // unknown return type
    void searchPrism(sead::Vector3f*, float, sead::IDelegate2<al::KCPrismData const*, al::KCPrismHeader const*>&); // unknown return type
    void searchPrismMinMax(sead::Vector3f const&, sead::Vector3f const&, sead::IDelegate2<al::KCPrismData const*, al::KCPrismHeader const*>&); // unknown return type
    void searchPrismArrow(sead::Vector3f const&, sead::Vector3f const&, sead::IDelegate2<al::KCPrismData const*, al::KCPrismHeader const*>&); // unknown return type
    void searchPrismDisk(sead::Vector3f const&, sead::Vector3f const&, float, float, sead::IDelegate2<al::KCPrismData const*, al::KCPrismHeader const*>&); // unknown return type
    bool isParallelNormal(al::KCPrismData const*, al::KCPrismHeader const*) const; // likely return type
    sead::Vector3f* getFaceNormal(al::KCPrismData const*, al::KCPrismHeader const*) const; // likely return type
    sead::Vector3f* getEdgeNormal1(al::KCPrismData const*, al::KCPrismHeader const*) const; // likely return type
    sead::Vector3f* getEdgeNormal2(al::KCPrismData const*, al::KCPrismHeader const*) const; // likely return type
    sead::Vector3f* getEdgeNormal3(al::KCPrismData const*, al::KCPrismHeader const*) const; // likely return type
    void KCHitDisc(al::KCPrismData const*, al::KCPrismHeader const*, sead::Vector3f const&, sead::Vector3f const&, float, float, sead::Vector3f*, float*); // unknown return type
    int toIndex(al::KCPrismData const*, al::KCPrismHeader const*) const; // unknown return type
    sead::Vector3f* getNormal(unsigned int, al::KCPrismHeader const*) const; // likely return type
    void calXvec(sead::Vector3f const*, sead::Vector3f const*, sead::Vector3f* output); // unknown return type
    sead::Vector3f* getVertexData(unsigned int, al::KCPrismHeader const*) const; // unknown return type
    unsigned int getVertexNum(al::KCPrismHeader const*) const; // likely return type
    int getNormalNum(al::KCPrismHeader const*) const; // likely return type
    int getAttributeElementNum() const; // likely return type
    void* getAttributes(al::ByamlIter*, unsigned int, al::KCPrismHeader const*) const; // unknown return type
    void* getAttributes(al::ByamlIter*, al::KCPrismData const*) const; // unknown return type
    void objectSpaceToAreaOffsetSpace(sead::Vector3<unsigned int>*, sead::Vector3f const&, al::KCPrismHeader const*) const; // unknown return type
    void areaOffsetSpaceToObjectSpace(sead::Vector3f*, sead::Vector3<unsigned int> const&, al::KCPrismHeader const*) const; // unknown return type
    bool doBoxCheck(sead::Vector3f const*, sead::Vector3f const*, sead::Vector3<unsigned int>*, sead::Vector3<unsigned int>*, al::KCPrismHeader const*); // unknown return type
    void* calcAreaBlockOffset(sead::Vector3<unsigned int> const&, al::KCPrismHeader const*) const; // unknown return type
    void* calcChildBlockOffset(sead::Vector3<unsigned int> const&, int); // unknown return type
    al::KCPrismData* getBlockData(unsigned int const*, unsigned int); // unknown return type

    sead::PtrArray<al::KCPrismHeader> mKCPrismHeaders;
    void* mData;
    al::ByamlIter* mAttributes; // "%sAttribute.byml"
    unsigned char unk2[0x50 - 0x20];
};

}
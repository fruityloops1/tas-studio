#pragma once

#include "nlib/binaryreader.h"
#include "raylib.h"
#include "types.h"
#include <span>

namespace fl {

struct Vertex {
    fl::Vector3f normal;
    fl::Vector3f position;
};

struct Triangle {
    fl::Vector3f vertices[3];
    u16 attribute;

    inline fl::Vector3f getNormal()
    {
        fl::Vector3f a = vertices[1] - vertices[0];
        fl::Vector3f b = a.cross(vertices[2] - vertices[0]);
        return b.normalize();
    }
};

struct KCLModel {
    struct Prism {
        float length;
        u16 posIndex;
        u16 dirIndex;
        u16 normalIndex[3];
        u16 colFlags;
        u32 globalIndex;
    };

    float mPrismThickness = 0;
    fl::Vector3f mMinCoord;
    fl::Vector3f mMaxCoord;
    fl::Vector3i mCoordMask;
    fl::Vector3i mCoordShift;
    float mSphereRadius = 0;

    std::vector<fl::Vector3f> mPositions;
    std::vector<fl::Vector3f> mNormals;
    std::vector<Prism> mPrisms;

    KCLModel(nlib::BinaryReader& reader);

    Triangle getTriangle(const Prism& p) const;
};

class KCL {
    fl::Vector3f minCoord;
    fl::Vector3f maxCoord;
    fl::Vector3i coordShift;

    std::vector<KCLModel> mModels;

public:
    KCL(std::span<const u8> data);

    std::string toObj() const;
    std::string toMtl() const;
};

} // namespace fl
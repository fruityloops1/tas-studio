#include "file/KCollision.h"
#include "nlib/binaryreader.h"
#include "types.h"
#include <algorithm>
#include <set>
#include <sstream>
#include <unordered_map>

namespace fl {

KCL::KCL(std::span<const u8> data)
{
    nlib::BinaryReader reader(data, std::endian::little);
    NLIB_VERIFY(reader.read<u32>() == 0x0202, "KCL::KCL only Version 2 supported", 0);
    NLIB_VERIFY(reader.read<u32>() == 0x38, "KCL::KCL only little endian supported", 0);
    u32 modelListOffset = reader.read<u32>();
    u32 modelCount = reader.read<u32>();
    minCoord = reader.read<fl::Vector3f>();
    maxCoord = reader.read<fl::Vector3f>();
    coordShift = reader.read<fl::Vector3i>();
    u32 prismCount = reader.read<u32>();

    reader.seek(modelListOffset);
    for (int i = 0; i < modelCount; i++) {
        u32 modelOffset = reader.read<u32>();
        u32 o = reader.tell();
        mModels.push_back(KCLModel(reader));
        reader.seek(o);
    }
}

std::string KCL::toMtl() const
{
    std::stringstream mtl;
    std::set<u16> colIds;
    for (const KCLModel& model : mModels)
        for (const auto prism : model.mPrisms)
            colIds.insert(prism.colFlags);

    for (u16 col : colIds)
        mtl << "newmtl COL_" << col << "\n";
    return mtl.str();
}

std::string KCL::toObj() const
{
    std::stringstream obj;
    int i = 0;
    int posShift = 1;
    int normalShift = 1;

    std::vector<KCLModel> cols;
    std::set<u16> colIds;

    for (const KCLModel& model : mModels)
        for (const auto prism : model.mPrisms)
            colIds.insert(prism.colFlags);
    for (u16 colId : colIds)
        for (const KCLModel& model : mModels) {
            KCLModel colModel = model;
            colModel.mPrisms.clear();
            for (const auto prism : model.mPrisms)
                if (prism.colFlags == colId)
                    colModel.mPrisms.push_back(prism);
            cols.push_back(colModel);
        }

    for (const KCLModel& model : cols) {
        obj << "o COL_" << i << "\n";

        std::vector<fl::Vector3f> positions;
        std::vector<fl::Vector3f> normals;
        std::unordered_map<std::string, int> posTable;
        std::unordered_map<std::string, int> normalTable;

        for (const KCLModel::Prism& face : model.mPrisms) {
            Triangle triangle = model.getTriangle(face);
            fl::Vector3f normal = triangle.getNormal();

            for (fl::Vector3f& vertex : triangle.vertices) {
                std::string posKey = vertex.toString();
                std::string nrmKey = normal.toString();

                if (!posTable.contains(posKey)) {
                    posTable[posKey] = positions.size();
                    positions.push_back(vertex);
                }

                if (!normalTable.contains(nrmKey)) {
                    normalTable[nrmKey] = normals.size();
                    normals.push_back(normal);
                }
            }
        }

        for (const fl::Vector3f& pos : positions)
            obj << "v " << pos.x << " " << pos.y << " " << pos.z << "\n";
        for (const fl::Vector3f& normal : normals)
            obj << "vn " << normal.x << " " << normal.y << " " << normal.z << "\n";

        u16 curCol = -1;
        for (const KCLModel::Prism& face : model.mPrisms) {
            if (curCol != face.colFlags) {
                obj << "usemtl COL_" << face.colFlags << "\n";
                curCol = face.colFlags;
            }

            obj << "f ";
            Triangle triangle = model.getTriangle(face);
            fl::Vector3f normal = triangle.getNormal();
            for (fl::Vector3f& vertex : triangle.vertices) {
                int posIndex = posShift + posTable[vertex.toString()];
                int nrmIndex = normalShift + normalTable[normal.toString()];

                obj << posIndex << "//" << nrmIndex << " ";
            }
            obj << "\n";
        }

        posShift += positions.size();
        normalShift += normals.size();
        i++;
    }
    return obj.str();
}

KCLModel::KCLModel(nlib::BinaryReader& reader)
{
    u32 origin = reader.tell();
    u32 posArrayOffset = reader.read<u32>();
    u32 normalArrayOffset = reader.read<u32>();
    u32 prismArrayOffset = reader.read<u32>();
    u32 octreeOffset = reader.read<u32>(); // octree shit

    mPrismThickness = reader.read<float>();
    mMinCoord = reader.read<fl::Vector3f>();
    mMaxCoord = reader.read<fl::Vector3f>();
    mCoordMask = reader.read<fl::Vector3i>();
    mCoordShift = reader.read<fl::Vector3i>();
    mSphereRadius = reader.read<float>();

    u32 posCount = (normalArrayOffset - posArrayOffset) / sizeof(fl::Vector3f);
    u32 normalCount = (prismArrayOffset - normalArrayOffset) / sizeof(fl::Vector3f);
    u32 prismCount = (octreeOffset - prismArrayOffset) / sizeof(Prism);

    reader.seek(origin + posArrayOffset);
    for (int i = 0; i < posCount; i++)
        mPositions.push_back(reader.read<fl::Vector3f>());
    reader.seek(origin + normalArrayOffset);
    for (int i = 0; i < normalCount; i++)
        mNormals.push_back(reader.read<fl::Vector3f>());
    reader.seek(origin + prismArrayOffset);
    for (int i = 0; i < prismCount; i++)
        mPrisms.push_back(reader.read<Prism>());
}

Triangle KCLModel::getTriangle(const Prism& p) const
{
    fl::Vector3f a = mPositions[p.posIndex];
    fl::Vector3f crossA = mNormals[p.normalIndex[0]].cross(mNormals[p.dirIndex]);
    fl::Vector3f crossB = mNormals[p.normalIndex[1]].cross(mNormals[p.dirIndex]);
    fl::Vector3f b = a + crossB * (p.length / crossB.dot(mNormals[p.normalIndex[2]]));
    fl::Vector3f c = a + crossA * (p.length / crossA.dot(mNormals[p.normalIndex[2]]));

    return { { a, b, c }, p.colFlags };
}

} // namespace fl
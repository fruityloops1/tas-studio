#pragma once

#include "fl//OutPacket.h"
#include <cstring>
#include <sead/math/seadVector.h>

namespace fl::packets {

class CameraInfo : public fl::OutPacket {
    struct {
        sead::Vector3f pos;
        sead::Vector3f at;
        sead::Vector3f up;
        float fovy;
    } mData;

public:
    CameraInfo(const sead::Vector3f& pos, const sead::Vector3f& at, const sead::Vector3f& up, float fovy)
        : OutPacket(3)
    {
        mData.pos = pos;
        mData.at = at;
        mData.up = up;
        mData.fovy = fovy;
    }

    size_t calcSize() override { return sizeof(mData); }
    void construct(u8* out) override
    {
        *(typeof(mData)*)out = mData;
    }
};

class ActorAliveStatus : public fl::OutPacket {
    const u32 mAmount = 0;
    bool* const mData = nullptr;

public:
    ActorAliveStatus(bool* data, u32 amount)
        : OutPacket(5)
        , mAmount(amount)
        , mData(data)
    {
    }
    size_t calcSize() override
    {
        return sizeof(mAmount) + mAmount;
    }
    void construct(u8* out) override
    {
        *(u32*)out = mAmount;
        std::memcpy(&out[sizeof(mAmount)], mData, mAmount);
    }
};

class ActorUpdate : public fl::OutPacket {
public:
    struct Entry {
        u32 index;
        sead::Vector3f pos;
        sead::Vector3f scale;
        sead::Vector3f rotate;
    };

private:
    u32 mEntryAmount = 0;
    Entry* mEntries = nullptr;

public:
    ActorUpdate(Entry* data, u32 amount)
        : OutPacket(6)
        , mEntryAmount(amount)
        , mEntries(data)
    {
    }
    size_t calcSize() override
    {
        return sizeof(mEntryAmount) + sizeof(Entry) * mEntryAmount;
    }
    void construct(u8* out) override
    {
        *(u32*)out = mEntryAmount;
        std::memcpy(&out[4], mEntries, mEntryAmount * sizeof(Entry));
    }
};

class SceneInit : public fl::OutPacket {
public:
    SceneInit()
        : OutPacket(7)
    {
    }
};

class ActorInit : public fl::OutPacket {
    struct {
        u32 actorIndex;
        sead::Vector3f initTrans;
        sead::Vector3f initScale;
        sead::Vector3f initRotate;
    } mFixed;
    const char* mArchiveName = nullptr;
    const char* mKCLName = nullptr;

public:
    ActorInit(u32 actorIndex, const sead::Vector3f& trans, const sead::Vector3f& scale, const sead::Vector3f& rotate, const char* archiveName, const char* kclName)
        : OutPacket(4)
        , mFixed({ actorIndex,
              trans,
              scale,
              rotate })
        , mArchiveName(archiveName)
        , mKCLName(kclName)
    {
    }
    size_t calcSize() override
    {
        return sizeof(mFixed) + strlen(mArchiveName) + 1 + strlen(mKCLName) + 1;
    }
    void construct(u8* out) override
    {
        *(typeof(mFixed)*)out = mFixed;
        strcpy((char*)&out[sizeof(mFixed)], mArchiveName);
        int kclNameOffset = sizeof(mFixed) + strlen(mArchiveName) + 1;
        strcpy((char*)&out[kclNameOffset], mKCLName);
    }
};

class PlayerInfo : public fl::OutPacket {

public:
    struct Entry {
        float radius;
        sead::Vector3f pos;
    };

private:
    sead::Vector3f mTrans;
    sead::Vector3f mCappyTrans;
    Entry* mEntries = nullptr;
    u32 mEntryAmount = 0;

public:
    PlayerInfo(const sead::Vector3f& trans, const sead::Vector3f& cappyTrans, Entry* entries, u32 entryAmount)
        : OutPacket(2)
        , mTrans(trans)
        , mCappyTrans(cappyTrans)
        , mEntries(entries)
        , mEntryAmount(entryAmount)
    {
    }
    size_t calcSize() override { return sizeof(mTrans) + sizeof(mCappyTrans) + sizeof(Entry) * mEntryAmount; }
    void construct(u8* out) override
    {
        *(sead::Vector3f*)out = mTrans;
        *(sead::Vector3f*)&out[sizeof(mTrans)] = mCappyTrans;
        std::memcpy(&out[sizeof(mTrans) + sizeof(mCappyTrans)], mEntries, sizeof(Entry) * mEntryAmount);
    }
};

} // namespace fl::Packets
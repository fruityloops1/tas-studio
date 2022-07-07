#pragma once

#include <cstddef>
#include <sead/basis/seadTypes.h>

namespace fl {

class OutPacket {
    u8 mId = -1;

public:
    OutPacket() = delete;
    OutPacket(u8 id)
        : mId(id)
    {
    }
    operator u8() { return mId; }

    virtual size_t calcSize() { return 0; };
    virtual void construct(u8* out) {};
};

} // namespace fl
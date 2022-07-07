#pragma once

#include "types.h"
#include <cstddef>

namespace fl {

class OutPacket {
    u8 mId = -1;

public:
    OutPacket(u8 id)
        : mId(id)
    {
    }
    operator u8() { return mId; }

    virtual size_t calcSize() { return 0; };
    virtual void construct(u8* out) {};
};

} // namespace fl
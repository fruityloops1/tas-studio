#include "fl/TasServer.h"
#include "fl/OutPacket.h"

namespace fl {

TasServer& TasServer::instance()
{
    static TasServer server;
    return server;
}

namespace {
    class Log : public OutPacket {
        size_t mSize = 0;
        const char* const mData = nullptr;

    public:
        Log(const char* data, size_t size)
            : OutPacket(1)
            , mSize(size)
            , mData(data)
        {
        }
        size_t calcSize() override { return mSize; }
        void construct(u8* out) override
        {
            strncpy((char*)out, mData, mSize);
        }
    };
}

void TasServer::log(const char* msg, size_t size)
{
    Log packet(msg, size);
    sendPacket(packet);
}

void TasServer::log(const char* msg)
{
    log(msg, strlen(msg));
}

} // namespace fl
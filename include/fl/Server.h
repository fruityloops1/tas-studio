#pragma once

#include "fl/OutPacket.h"
#include "nn/os.h"
#include "nn/socket.h"
#include <cstdlib>
#include <cstring>
#include <sead/basis/seadTypes.h>

namespace fl {

class Server {
    constexpr static size_t sThreadStackSize = 0x2000;
    constexpr static size_t sPacketBufferSize = 0x1000;

    s32 mSocket = -1;
    sockaddr_in mAddress { 0 };
    sockaddr_in mClientAddr { 0 };
    bool mIsStarted = false;

    nn::os::ThreadType mRecvThread { 0 };
    void* mThreadStack = nullptr;

    void handlePacket(u8* data, size_t size);
    friend void threadFunc(void*);

protected:
    typedef void (Server::*receivePacket)(u8* data, size_t len);

    struct ReceivePacketList {
        const Server::receivePacket* packets = nullptr;
        u8 amount = 0;

        template <u8 N>
        constexpr ReceivePacketList(const Server::receivePacket (&packets)[N])
        {
            this->packets = packets;
            amount = N;
        }
    };
    ReceivePacketList mPackets;

public:
    virtual ~Server();
    Server(u16 port, const ReceivePacketList& packets);

    void start();
    bool tryStart();

    void sendPacket(OutPacket& packet);

    void receiveInit(u8* data, size_t len);
};

} // namespace fl
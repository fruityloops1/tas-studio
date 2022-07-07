#pragma once

#include "client/OutPacket.h"
#include "types.h"
#include <netinet/in.h>
#include <thread>

namespace fl {

class Client {
    constexpr static size_t sPacketBufferSize = 0x10000;

    sockaddr_in mServerAddress;
    sockaddr mClientAddress;
    s32 mSocket = -1;

    std::thread mRecvThread;

protected:
    typedef void (Client::*receivePacket)(u8* data, size_t len);

    struct ReceivePacketList {
        const Client::receivePacket* packets = nullptr;
        u8 amount = 0;

        template <u8 N>
        constexpr ReceivePacketList(const Client::receivePacket (&packets)[N])
            : packets(packets)
            , amount(N)
        {
        }
    };
    ReceivePacketList mPackets;

public:
    Client(const ReceivePacketList& packets)
        : mPackets(packets)
    {
    }

    void connect(const char* address, u16 port);

    void sendPacket(OutPacket&);
    void handlePacket(u8* data, size_t size);

    void receiveInit(u8* data, size_t size);

    friend void threadFunc(Client*);
};

} // namespace fl
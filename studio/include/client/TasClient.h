#pragma once

#include "client/Client.h"

namespace fl {

class TasClient : public Client {
public:
    TasClient()
        : Client(sPackets)
    {
    }
    void receiveLog(u8* data, size_t len);
    void receivePlayerInfo(u8* data, size_t len);
    void receiveCameraInfo(u8* data, size_t len);
    void receiveActorInit(u8* data, size_t len);

private:
    constexpr static Client::receivePacket sPackets[] = {
        &Client::receiveInit,
        (Client::receivePacket)&TasClient::receiveLog,
        (Client::receivePacket)&TasClient::receivePlayerInfo,
        (Client::receivePacket)&TasClient::receiveCameraInfo,
        (Client::receivePacket)&TasClient::receiveActorInit
    };
};

} // namespace fl
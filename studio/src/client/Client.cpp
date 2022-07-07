#include "client/Client.h"
#include "client/OutPacket.h"
#include <arpa/inet.h>
#include <stdexcept>
#include <sys/socket.h>

namespace fl {

void threadFunc(Client* client)
{
    u8 buf[Client::sPacketBufferSize] { 0 };
    size_t len = 0;
    u32 serverSize = sizeof(client->mServerAddress);

    while (true) {
        len = recvfrom(client->mSocket, buf, Client::sPacketBufferSize, MSG_WAITALL, (sockaddr*)&client->mServerAddress, &serverSize);

        client->handlePacket(buf, len);
    }
}

namespace {
    class Init : public OutPacket {
    public:
        Init()
            : OutPacket(0)
        {
        }
    };
}

void Client::connect(const char* address, u16 port)
{
    mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mSocket < -1)
        throw std::runtime_error("Can't create socket");
    mServerAddress.sin_family = AF_INET;
    mServerAddress.sin_port = htons(port);
    mServerAddress.sin_addr.s_addr = inet_addr(address);

    sockaddr_in client = { 0 };
    client.sin_port = htons(port - 1);
    client.sin_family = AF_INET;
    if (bind(mSocket, (sockaddr*)&client, sizeof(client)) < 0)
        throw std::runtime_error("Can't bind socket");

    mRecvThread = std::thread(threadFunc, this);

    Init initPacket;
    sendPacket(initPacket);
}

void Client::handlePacket(u8* data, size_t size)
{
    u8 type = data[0];
    if (type >= mPackets.amount)
        throw std::runtime_error("invalid packet id received");
    (this->*mPackets.packets[type])(data + 1, size - 1);
}

void Client::sendPacket(OutPacket& packet)
{
    u32 size = packet.calcSize();
    u8 data[size + 1];

    data[0] = packet;
    packet.construct(data + 1);
    sendto(mSocket, data, size + 1, 0, (sockaddr*)&mServerAddress, sizeof(mServerAddress));
}

void Client::receiveInit(u8* data, size_t size)
{
    printf("Successfully connected\n");
}

} // namespace fl
#pragma once

#include "fl/Server.h"
#include "al/util.hpp"
#include "diag/assert.hpp"
#include "fl/OutPacket.h"
#include "fl/TasHeap.h"
#include "lib.hpp"
#include "nn/os.h"
#include "nn/socket.h"
#include <sead/basis/seadNew.h>

namespace fl {

void threadFunc(void* serverPtr)
{
    Server* server = (Server*)serverPtr;

    nn::TimeSpan wait = nn::TimeSpan::FromNanoSeconds(1000000);
    u8 buf[Server::sPacketBufferSize] { 0 };
    size_t len = 0;
    u32 clientSize = sizeof(server->mClientAddr);

    while (true) {
        len = nn::socket::RecvFrom(server->mSocket, buf, Server::sPacketBufferSize, 0, &server->mClientAddr, &clientSize);

        server->handlePacket(buf, len);
        nn::os::YieldThread();
        nn::os::SleepThread(wait);
    }
}

Server::Server(u16 port, const ReceivePacketList& packets)
    : mPackets(packets)
{
    memset(&mAddress, 0, sizeof(mAddress));
    memset(&mClientAddr, 0, sizeof(mClientAddr));

    mAddress.family = 2;
    mAddress.address.data = 0;
    mAddress.port = nn::socket::InetHtons(port);

    mThreadStack = fl::getTasHeap()->alloc(sThreadStackSize, 0x1000);
}

Server::~Server()
{
    nn::os::SuspendThread(&mRecvThread);
    nn::os::DestroyThread(&mRecvThread);
    fl::getTasHeap()->free(mThreadStack);
}

void Server::start()
{
    mSocket = nn::socket::Socket(2, 2, 0);
    R_ABORT_UNLESS(mSocket);

    if (R_FAILED(nn::socket::Bind(mSocket, &mAddress, sizeof(mAddress))))
        EXL_ABORT(nn::socket::GetLastErrno());

    nn::os::CreateThread(&mRecvThread, threadFunc, this, mThreadStack, sThreadStackSize, 16, 0);
    nn::os::SetThreadName(&mRecvThread, "fl::Server RecvThread");
    nn::os::StartThread(&mRecvThread);
    mIsStarted = true;
}

bool Server::tryStart()
{
    if (mIsStarted)
        return false;
    start();
    return true;
}

void Server::handlePacket(u8* data, size_t size)
{
    u8 type = data[0];
    if (type >= mPackets.amount)
        EXL_ABORT(0x42069, "invalid packet id received (%d)", type);
    (this->*mPackets.packets[type])(data + 1, size - 1);
}

void Server::sendPacket(OutPacket& packet)
{
    u32 size = packet.calcSize();
    u8 data[size + 1];

    data[0] = packet;
    packet.construct(data + 1);
    nn::socket::SendTo(mSocket, data, size + 1, 0, &mClientAddr, sizeof(mClientAddr));
}

namespace {

    class PongInit : public OutPacket {
    public:
        PongInit()
            : OutPacket(0)
        {
        }
    };

}

void Server::receiveInit(u8* data, size_t len)
{
    PongInit pong;
    sendPacket(pong);
}

} // namespace fl
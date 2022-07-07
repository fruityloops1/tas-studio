#pragma once

#include "fl/Server.h"
#include <cstdio>

namespace fl {

class TasServer : public Server {
public:
    TasServer()
        : Server(7032, sPackets)
    {
    }

    static TasServer& instance();

    void log(const char* msg);
    void log(const char* msg, size_t size);

    template <typename... Args>
    void log(const char* fmt, Args... args)
    {
        size_t size = snprintf(nullptr, 0, fmt, args...);
        char data[size + 1];
        snprintf(data, size, fmt, args...);
        log((const char*)data, size);
    }

private:
    constexpr static Server::receivePacket sPackets[] = { (Server::receivePacket)&TasServer::receiveInit };
};

} // namespace fl
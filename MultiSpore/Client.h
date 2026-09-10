#pragma once

#include <string>

namespace Client
{
    class Client
    {
    public:
        Client();
        ~Client();

        bool Connect(const std::string& host, unsigned short port);
        void Disconnect();

        bool IsConnected() const;

    private:
        bool connected = false;
    };
}
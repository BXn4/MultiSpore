#include "stdafx.h"
#include "Client.h"
#include "Log.h"

Log::Log logger;

namespace Client
{
    Client::Client()
    {
    }

    Client::~Client()
    {
        Disconnect();
    }

    bool Client::Connect(const std::string& host, unsigned short port)
    {
        logger.Debug("Connecting to %s:%hu", host.c_str(), port);
        if (connected) {
            Disconnect();
        }

        connected = true;
        return connected;
    }

    void Client::Disconnect()
    {
        if (!connected)
            return;

        connected = false;
    }

    bool Client::IsConnected() const
    {
        return connected;
    }
}
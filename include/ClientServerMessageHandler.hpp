#pragma once

#include "MessageHandler.hpp"

class ClientServerMessageHandler : public MessageHandler
{
public:
    ClientServerMessageHandler() {}
    ~ClientServerMessageHandler() {}

    virtual bool HandleMessage(Message *message, ENetPeer *peer) override;
};
#pragma once

#include "Message.hpp"
#include <string>

class ServerMessage : public Message
{
public:
    ServerMessage(std::string message) : Message(MessageType::SERVER_MESSAGE), message(message) {}

    virtual json ToJson() override;

    std::string GetServerMessage() { return message; }

    void SetServerMessage(std::string message) { this->message = message; }

private:
    std::string message;
};

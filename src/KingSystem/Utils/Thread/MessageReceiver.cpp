#include "KingSystem/Utils/Thread/MessageReceiver.h"

namespace ksys {

u32 MessageReceiver::sId{};

MessageReceiver::MessageReceiver() : mTransceiverId(sId, this) {}

MessageReceiver::~MessageReceiver() = default;

MesTransceiverId* MessageReceiver::getId() {
    return &mTransceiverId;
}

int MessageReceiver::receive(const Message& message) {
    return true;
}

void MessageReceiver::receive(const MessageAck& ack) {}

}  // namespace ksys

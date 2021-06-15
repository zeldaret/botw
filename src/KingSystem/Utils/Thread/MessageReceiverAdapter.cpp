#include "KingSystem/Utils/Thread/MessageReceiverAdapter.h"

namespace ksys {

MessageReceiverAdapter::MessageReceiverAdapter(MessageReceiver* wrapped) : mReceiver(wrapped) {}

MessageReceiverAdapter::~MessageReceiverAdapter() = default;

int MessageReceiverAdapter::handleMessage(const Message& message) {
    return mReceiver->receive(message);
}

void MessageReceiverAdapter::handleAck(const MessageAck& ack) {
    return mReceiver->receive(ack);
}

}  // namespace ksys

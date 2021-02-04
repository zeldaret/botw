#include "KingSystem/Utils/Thread/MessageTransceiverRxOnly.h"

namespace ksys {

MessageTransceiverRxOnly::MessageTransceiverRxOnly(IHandler& handler) : mReceiver(handler) {
    registerReceiver(mReceiver);
}

MessageTransceiverRxOnly::~MessageTransceiverRxOnly() {
    deregisterReceiver(mReceiver);
}

MessageReceiverEx* MessageTransceiverRxOnly::getReceiver() {
    return &mReceiver;
}

MessageTransceiverRxOnly::Receiver::~Receiver() = default;

int MessageTransceiverRxOnly::Receiver::handleMessage(const Message& message) {
    return mHandler.handleMessage(message);
}

}  // namespace ksys

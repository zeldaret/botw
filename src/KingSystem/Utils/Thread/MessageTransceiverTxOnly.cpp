#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"
#include "KingSystem/Utils/Thread/MessageTransceiverCommon.h"

namespace ksys {

MessageTransceiverTxOnly::MessageTransceiverTxOnly(IHandler& handler) : mReceiver(handler) {
    registerReceiver(mReceiver);
}

MessageTransceiverTxOnly::~MessageTransceiverTxOnly() {
    deregisterReceiver(mReceiver);
}

MessageReceiverEx* MessageTransceiverTxOnly::getReceiver() {
    return &mReceiver;
}

bool MessageTransceiverTxOnly::sendMessage(const MesTransceiverId& dest, const MessageType& type,
                                           void* user_data, bool ack) {
    return sendMessageImpl(this, dest, type, user_data, ack);
}

bool MessageTransceiverTxOnly::sendMessageOnProcessingThread(const MesTransceiverId& dest,
                                                             const MessageType& type,
                                                             void* user_data, bool ack) {
    return sendMessageOnProcessingThreadImpl(this, dest, type, user_data, ack);
}

bool MessageTransceiverTxOnly::sendMessage(IMessageBroker& broker, const MessageType& type,
                                           void* user_data, bool ack) {
    return sendMessageImpl(this, broker, type, user_data, ack);
}

bool MessageTransceiverTxOnly::sendMessageOnProcessingThread(IMessageBroker& broker,
                                                             const MessageType& type,
                                                             void* user_data, bool ack) {
    return sendMessageOnProcessingThreadImpl(this, broker, type, user_data, ack);
}

MessageTransceiverTxOnly::Receiver::~Receiver() = default;

void MessageTransceiverTxOnly::Receiver::handleAck(const MessageAck& ack) {
    mHandler.handleAck(ack);
}

}  // namespace ksys

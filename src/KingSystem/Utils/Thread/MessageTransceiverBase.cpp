#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"
#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "KingSystem/Utils/Thread/MessageReceiverEx.h"

namespace ksys {

MessageDispatcherBase* MessageTransceiverBase::sDispatcher{};

MessageTransceiverBase::MessageTransceiverBase() = default;

MessageTransceiverBase::~MessageTransceiverBase() = default;

bool MessageTransceiverBase::checkReceiverFlag() {
    return getReceiver()->checkFlag();
}

bool MessageTransceiverBase::isWaitingForAck() {
    return getReceiver()->isWaitingForAck();
}

bool MessageTransceiverBase::sendMessage(const MesTransceiverId& dest, const MessageType& type,
                                         void* user_data, bool ack) {
    return false;
}

bool MessageTransceiverBase::sendMessageOnProcessingThread(const MesTransceiverId& dest,
                                                           const MessageType& type, void* user_data,
                                                           bool ack) {
    return false;
}

bool MessageTransceiverBase::sendMessage(IMessageBroker& broker, const MessageType& type,
                                         void* user_data, bool ack) {
    return false;
}

bool MessageTransceiverBase::sendMessageOnProcessingThread(IMessageBroker& broker,
                                                           const MessageType& type, void* user_data,
                                                           bool ack) {
    return false;
}

MessageDispatcherBase* MessageTransceiverBase::getDispatcher() {
    return mDispatcher;
}

void MessageTransceiverBase::setGlobalDispatcher(MessageDispatcherBase* dispatcher) {
    sDispatcher = dispatcher;
}

IMessageBrokerRegister* MessageTransceiverBase::getRegister(IMessageBroker& broker) const {
    return broker.getRegister();
}

}  // namespace ksys

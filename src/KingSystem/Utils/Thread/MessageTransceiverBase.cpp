#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"
#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "KingSystem/Utils/Thread/MessageReceiverEx.h"

namespace ksys {

MessageDispatcherBase* MessageTransceiverBase::sDispatcher{};

MessageTransceiverBase::MessageTransceiverBase() = default;

MessageTransceiverBase::~MessageTransceiverBase() = default;

bool MessageTransceiverBase::checkReceiverFlag() const {
    return getReceiver()->checkFlag();
}

bool MessageTransceiverBase::checkReceiverCounter() const {
    return getReceiver()->checkCounter();
}

bool MessageTransceiverBase::m2() {
    return false;
}

bool MessageTransceiverBase::m3() {
    return false;
}

bool MessageTransceiverBase::m4() {
    return false;
}

bool MessageTransceiverBase::m5() {
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

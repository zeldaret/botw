#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"
#include "KingSystem/Utils/Thread/MessageTransceiverIdGenEx.h"

namespace ksys {

MessageDispatcherBase* MessageTransceiverBase::sDispatcher{};

MessageTransceiverBase::MessageTransceiverBase() = default;

MessageTransceiverBase::~MessageTransceiverBase() = default;

bool MessageTransceiverBase::checkGeneratorFlag() const {
    return getGenerator()->checkFlag();
}

bool MessageTransceiverBase::checkGeneratorCounter() const {
    return getGenerator()->checkCounter();
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

}  // namespace ksys

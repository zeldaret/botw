#include "KingSystem/Utils/Thread/MessageTransceiver.h"

namespace ksys {

MessageTransceiver::MessageTransceiver() = default;

MessageTransceiver::~MessageTransceiver() = default;

bool MessageTransceiver::m2() {
    return false;
}

bool MessageTransceiver::m3() {
    return false;
}

bool MessageTransceiver::m4() {
    return false;
}

bool MessageTransceiver::m5() {
    return false;
}

MessageDispatcherBase* MessageTransceiver::getDispatcher() {
    return mDispatcher;
}

void MessageTransceiver::setGlobalDispatcher(MessageDispatcherBase* dispatcher) {
    sDispatcher = dispatcher;
}

}  // namespace ksys

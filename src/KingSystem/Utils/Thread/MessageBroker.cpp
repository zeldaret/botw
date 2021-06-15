#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace ksys {

IMessageBroker::IMessageBroker() = default;

IMessageBroker::~IMessageBroker() = default;

bool IMessageBroker::registerTransceiver(const MessageTransceiverBase& transceiver) {
    return getRegister()->registerTransceiver(*transceiver.getId());
}

void IMessageBroker::deregisterTransceiver(const MessageTransceiverBase& transceiver) {
    return getRegister()->deregisterTransceiver(*transceiver.getId());
}

int IMessageBroker::countTransceivers() {
    return getRegister()->countTransceivers();
}

}  // namespace ksys

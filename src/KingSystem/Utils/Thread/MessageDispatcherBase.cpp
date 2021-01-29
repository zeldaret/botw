#include "KingSystem/Utils/Thread/MessageDispatcherBase.h"
#include "KingSystem/Utils/Thread/MessageTransceiver.h"

namespace ksys {

MessageDispatcherBase::MessageDispatcherBase() = default;

MessageDispatcherBase::~MessageDispatcherBase() = default;

void MessageDispatcherBase::setAsGlobalInstance() {
    MessageTransceiver::setGlobalDispatcher(this);
}

}  // namespace ksys

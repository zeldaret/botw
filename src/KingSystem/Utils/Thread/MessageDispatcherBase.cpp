#include "KingSystem/Utils/Thread/MessageDispatcherBase.h"
#include "KingSystem/Utils/Thread/MessageTransceiverBase.h"

namespace ksys {

MessageDispatcherBase::MessageDispatcherBase() = default;

MessageDispatcherBase::~MessageDispatcherBase() = default;

void MessageDispatcherBase::setAsGlobalInstance() {
    MessageTransceiverBase::setGlobalDispatcher(this);
}

}  // namespace ksys

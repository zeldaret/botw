#include "KingSystem/Utils/Thread/MessageReceiverAdapter.h"

namespace ksys {

MessageReceiverAdapter::MessageReceiverAdapter(MessageReceiver* wrapped)
    : mReceiver(wrapped) {}

MessageReceiverAdapter::~MessageReceiverAdapter() = default;

bool MessageReceiverAdapter::m6(void* x) {
    return mReceiver->m1(x);
}

void MessageReceiverAdapter::m7(void* x) {
    return mReceiver->m2(x);
}

}  // namespace ksys

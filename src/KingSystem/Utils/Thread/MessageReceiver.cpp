#include "KingSystem/Utils/Thread/MessageReceiver.h"

namespace ksys {

u32 MessageReceiver::sId{};

MessageReceiver::MessageReceiver() : mTransceiverId(sId, this) {}

MessageReceiver::~MessageReceiver() = default;

MesTransceiverId* MessageReceiver::getId() {
    return &mTransceiverId;
}

bool MessageReceiver::m1(void*) {
    return true;
}

void MessageReceiver::m2(void* x) {}

}  // namespace ksys

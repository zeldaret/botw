#include "KingSystem/Utils/Thread/MessageReceiverEx.h"

namespace ksys {

MessageReceiverEx::MessageReceiverEx() = default;

MessageReceiverEx::~MessageReceiverEx() = default;

int MessageReceiverEx::receive(const Message& message) {
    return handleMessage(message);
}

void MessageReceiverEx::receive(const MessageAck& ack) {
    handleAck(ack);
    --mCounter;
    static_cast<void>(mCounter.load());
}

bool MessageReceiverEx::checkFlag() const {
    return mFlag && *mFlag == 1;
}

bool MessageReceiverEx::checkCounter() const {
    return mCounter > 0;
}

void MessageReceiverEx::setFlag(bool update_counter) {
    if (mFlag) {
        if (update_counter)
            mCounter.increment();
        *mFlag = 1;
    }
}

int MessageReceiverEx::handleMessage(const Message& message) {
    return true;
}

void MessageReceiverEx::handleAck(const MessageAck& ack) {}

void MessageReceiverEx::setFlagPointer(u8* ptr) {
    if (ptr) {
        mFlag = ptr;
        *mFlag = 0;
    }
}

void MessageReceiverEx::clearFlagPointer() {
    *mFlag = 0;
    mFlag = nullptr;
}

}  // namespace ksys

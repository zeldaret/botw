#include "KingSystem/Utils/Thread/MessageReceiverEx.h"

namespace ksys {

MessageReceiverEx::MessageReceiverEx() = default;

MessageReceiverEx::~MessageReceiverEx() = default;

bool MessageReceiverEx::m1(void* x) {
    return m6(x);
}

void MessageReceiverEx::m2(void* x) {
    m7(x);
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

bool MessageReceiverEx::m6(void* x) {
    return true;
}

void MessageReceiverEx::m7(void* x) {}

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

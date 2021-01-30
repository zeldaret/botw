#include "KingSystem/Utils/Thread/MessageTransceiverIdGenEx.h"

namespace ksys {

MesTransceiverIdGenEx::MesTransceiverIdGenEx() = default;

MesTransceiverIdGenEx::~MesTransceiverIdGenEx() = default;

bool MesTransceiverIdGenEx::m1(void* x) {
    return m6(x);
}

void MesTransceiverIdGenEx::m2(void* x) {
    m7(x);
    --mCounter;
    static_cast<void>(mCounter.load());
}

bool MesTransceiverIdGenEx::checkFlag() const {
    return mFlag && *mFlag == 1;
}

bool MesTransceiverIdGenEx::checkCounter() const {
    return mCounter > 0;
}

void MesTransceiverIdGenEx::setFlag(bool update_counter) {
    if (mFlag) {
        if (update_counter)
            mCounter.increment();
        *mFlag = 1;
    }
}

bool MesTransceiverIdGenEx::m6(void* x) {
    return true;
}

void MesTransceiverIdGenEx::m7(void* x) {}

void MesTransceiverIdGenEx::setFlagPointer(u8* ptr) {
    if (ptr) {
        mFlag = ptr;
        *mFlag = 0;
    }
}

void MesTransceiverIdGenEx::clearFlagPointer() {
    *mFlag = 0;
    mFlag = nullptr;
}

}  // namespace ksys

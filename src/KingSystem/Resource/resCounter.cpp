#include "KingSystem/Resource/resCounter.h"

namespace ksys::res {

CounterBase::CounterBase(sead::Heap*) {}

CounterBase::~CounterBase() = default;

bool CounterBase::setData(const CounterBase::Data& data) {
    return doSetData_(data);
}

void CounterBase::incrementRef() {
    mRefCount.increment();
}

void CounterBase::decrementRef() {
    if (mRefCount)
        mRefCount.decrement();
}

void CounterBase::setFlag() {
    mFlag = true;
}

void CounterBase::reset() {
    [[maybe_unused]] const auto count = mRefCount;
    mFlag = false;
}

bool CounterBase::isFlagSet() const {
    return mFlag;
}

bool Counter::doSetData_(const CounterBase::Data& data) {
    mData = data.mData;
    return true;
}

}  // namespace ksys::res

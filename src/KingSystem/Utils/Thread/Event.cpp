#include "KingSystem/Utils/Thread/Event.h"

namespace ksys::util {

Event::Event() = default;

Event::Event(sead::Heap* disposer_heap) : mEvent(disposer_heap) {}

Event::Event(bool manual_reset) : mManualReset(manual_reset), mEvent(manual_reset) {}

Event::Event(sead::Heap* disposer_heap, bool manual_reset)
    : mManualReset(manual_reset), mEvent(disposer_heap, manual_reset) {}

Event::Event(sead::Heap* disposer_heap, sead::IDisposer::HeapNullOption heap_null_option,
             bool manual_reset)
    : mManualReset(manual_reset), mEvent(disposer_heap, heap_null_option, manual_reset) {}

Event::~Event() = default;

void Event::initialize(bool manual_reset) {
    mManualReset = manual_reset;
    mEvent.initialize(manual_reset);
}

void Event::wait() {
    if (!mSignalSet || !mManualReset)
        mEvent.wait();
}

bool Event::wait(sead::TickSpan duration) {
    return (mSignalSet && mManualReset) || mEvent.wait(duration);
}

void Event::setSignal() {
    if (mSignalSet == 1 && mManualReset)
        return;

    mSignalSet.exchange(1);
    mEvent.setSignal();
}

void Event::resetSignal() {
    if (!mSignalSet && mManualReset)
        return;

    mEvent.resetSignal();
    mSignalSet.exchange(0);
}

bool Event::isSignalSet() const {
    return mSignalSet == 1;
}

}  // namespace ksys::util

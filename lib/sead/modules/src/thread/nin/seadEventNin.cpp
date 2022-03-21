#include "basis/seadRawPrint.h"
#include "thread/seadEvent.h"

namespace sead
{
Event::Event() : IDisposer() {}

Event::Event(bool manual_reset) : Event()
{
    initialize(manual_reset);
}

Event::Event(Heap* disposer_heap) : Event(disposer_heap, HeapNullOption::UseSpecifiedOrContainHeap)
{
}

Event::Event(Heap* disposer_heap, bool manual_reset) : Event(disposer_heap)
{
    initialize(manual_reset);
}

Event::Event(Heap* disposer_heap, IDisposer::HeapNullOption heap_null_option)
    : IDisposer(disposer_heap, heap_null_option)
{
}

Event::Event(Heap* disposer_heap, IDisposer::HeapNullOption heap_null_option, bool manual_reset)
    : Event(disposer_heap, heap_null_option)
{
    initialize(manual_reset);
}

Event::~Event()
{
    setInitialized(false);
    nn::os::FinalizeLightEvent(&mEventInner);
}

void Event::initialize(bool manual_reset)
{
#ifdef SEAD_DEBUG
    SEAD_ASSERT_MSG(!mInitialized, "Event is already initialized.");
#endif
    nn::os::InitializeLightEvent(&mEventInner, false,
                                 manual_reset ? nn::os::EventClearMode_ManualClear :
                                                nn::os::EventClearMode_AutoClear);
    setInitialized(true);
}

void Event::wait()
{
#ifdef SEAD_DEBUG
    SEAD_ASSERT_MSG(mInitialized, "Event is not initialized.");
#endif
    nn::os::WaitLightEvent(&mEventInner);
}

bool Event::wait(TickSpan duration)
{
#ifdef SEAD_DEBUG
    SEAD_ASSERT_MSG(mInitialized, "Event is not initialized.");
#endif
    return nn::os::TimedWaitLightEvent(&mEventInner, nn::os::ConvertToTimeSpan(duration.toTicks()));
}

void Event::setSignal()
{
#ifdef SEAD_DEBUG
    SEAD_ASSERT_MSG(mInitialized, "Event is not initialized.");
#endif
    nn::os::SignalLightEvent(&mEventInner);
}

void Event::resetSignal()
{
#ifdef SEAD_DEBUG
    SEAD_ASSERT_MSG(mInitialized, "Event is not initialized.");
#endif
    nn::os::ClearLightEvent(&mEventInner);
}
}  // namespace sead

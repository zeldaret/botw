#pragma once

#ifdef NNSDK
#include <nn/os.h>
#endif

#include "heap/seadDisposer.h"
#include "time/seadTickSpan.h"

namespace sead
{
class Heap;

class Event : public IDisposer
{
public:
    Event();
    explicit Event(bool manual_reset);
    explicit Event(Heap* disposer_heap);
    Event(Heap* disposer_heap, bool manual_reset);
    Event(Heap* disposer_heap, IDisposer::HeapNullOption heap_null_option);
    Event(Heap* disposer_heap, IDisposer::HeapNullOption heap_null_option, bool manual_reset);
    ~Event() override;

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    void initialize(bool manual_reset);
    void wait();
    bool wait(TickSpan duration);
    void setSignal();
    void resetSignal();

private:
    void setInitialized([[maybe_unused]] bool initialized)
    {
#ifdef SEAD_DEBUG
        mInitialized = initialized;
#endif
    }

#ifdef NNSDK
    nn::os::LightEventType mEventInner;
#else
#error "Unknown platform"
#endif

#ifdef SEAD_DEBUG
    bool mInitialized = false;
#endif
};
}  // namespace sead

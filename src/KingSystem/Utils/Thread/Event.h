#pragma once

#include <thread/seadAtomic.h>
#include <thread/seadEvent.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class Event {
public:
    Event();
    explicit Event(sead::Heap* disposer_heap);
    explicit Event(bool manual_reset);
    Event(sead::Heap* disposer_heap, bool manual_reset);
    Event(sead::Heap* disposer_heap, sead::IDisposer::HeapNullOption heap_null_option,
          bool manual_reset);
    virtual ~Event();

    void initialize(bool manual_reset);
    void wait();
    bool wait(sead::TickSpan duration);
    void setSignal();
    void resetSignal();

    bool isSignalSet() const;

private:
    bool mManualReset = false;
    sead::Atomic<u32> mSignalSet = 0;
    sead::Event mEvent;
};
KSYS_CHECK_SIZE_NX150(sead::Event, 0x30);
KSYS_CHECK_SIZE_NX150(Event, 0x40);

}  // namespace ksys::util

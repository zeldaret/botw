#pragma once

#include "prim/seadDelegate.h"
#include "prim/seadDelegateEventSlot.h"

namespace sead
{
class AssertConfig
{
public:
    using AssertEvent = DelegateEvent<const char*>;

    static void registerCallback(AssertEvent::Slot& slot);
    static void unregisterCallback(AssertEvent::Slot& slot);
    static void registerFinalCallback(IDelegate1<const char*>* cb);
    static void execCallbacks(const char* assertMessage);

private:
    static AssertEvent sAssertEvent;
    static IDelegate1<char const*>* sFinalCallback;
};
}  // namespace sead

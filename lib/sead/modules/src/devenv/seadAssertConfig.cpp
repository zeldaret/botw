#include "devenv/seadAssertConfig.h"

namespace sead
{
AssertConfig::AssertEvent AssertConfig::sAssertEvent{};
IDelegate1<const char*>* AssertConfig::sFinalCallback = nullptr;

void AssertConfig::registerCallback(AssertEvent::Slot& slot)
{
    sAssertEvent.connect(slot);
}

void AssertConfig::unregisterCallback(AssertEvent::Slot& slot)
{
    sAssertEvent.disconnect(slot);
}

void AssertConfig::registerFinalCallback(IDelegate1<const char*>* cb)
{
    sFinalCallback = cb;
}

void AssertConfig::execCallbacks(const char* assertMessage)
{
    sAssertEvent.emit(assertMessage);
    if (sFinalCallback)
        sFinalCallback->invoke(assertMessage);
}
}  // namespace sead

#include "thread/seadThreadUtil.h"
#include "basis/seadRawPrint.h"

namespace sead
{
s32 ThreadUtil::ConvertPrioritySeadToPlatform(s32 prio)
{
    SEAD_ASSERT(prio >= 0);
    SEAD_ASSERT(prio < 32);
    return prio;
}

s32 ThreadUtil::ConvertPriorityPlatformToSead(s32 prio)
{
    SEAD_ASSERT(prio >= 0);
    SEAD_ASSERT(prio < 32);
    return prio;
}

// NON_MATCHING: two instructions are reordered; maybe this is inline assembly?
uintptr_t ThreadUtil::GetCurrentStackPointer()
{
    volatile uintptr_t x = 0;
    uintptr_t y;
    x = uintptr_t(&y);
    return x;
}
}  // namespace sead

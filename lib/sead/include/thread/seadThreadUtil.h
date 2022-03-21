#pragma once

#include "basis/seadTypes.h"

namespace sead
{
class ThreadUtil
{
public:
    static s32 ConvertPrioritySeadToPlatform(s32 prio);
    static s32 ConvertPriorityPlatformToSead(s32 prio);
    static uintptr_t GetCurrentStackPointer();
};
}  // namespace sead

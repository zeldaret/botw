#pragma once

#include <thread/seadCriticalSection.h>

namespace ksys::res {

extern sead::CriticalSection gCacheCriticalSection;

void lockCacheCriticalSection();
void unlockCacheCriticalSection();

}  // namespace ksys::res

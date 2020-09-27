#include "KingSystem/Resource/resCacheCriticalSection.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::res {

[[maybe_unused]] static util::InitTimeInfo sInitTimeInfo;
sead::CriticalSection gCacheCriticalSection;

void lockCacheCriticalSection() {
    gCacheCriticalSection.lock();
}

void unlockCacheCriticalSection() {
    gCacheCriticalSection.unlock();
}

}  // namespace ksys::res

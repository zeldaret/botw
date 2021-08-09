#include "KingSystem/System/DebugFinder.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(DebugFinder)

DebugFinder::DebugFinder() = default;

void DebugFinder::init(sead::Heap* heap) {}

}  // namespace ksys


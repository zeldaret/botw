#include "KingSystem/Utils/TrackerStub.h"

namespace ksys::util {

TrackerStub makeTracker(const sead::SafeString& name, u32 x) {
    return {};
}

void TrackerStub::destroy() {}

TrackerStubScope::TrackerStubScope(TrackerStub tracker, const sead::SafeString& name,
                                   const sead::SafeString& caller, s32 level) {
    mTracker = tracker;
}

TrackerStubScope::~TrackerStubScope() {
#ifdef MATCHING_HACK_NX_CLANG
    // force D1 to be non-trivial
    __builtin_assume(true);
#endif
}

}  // namespace ksys::util

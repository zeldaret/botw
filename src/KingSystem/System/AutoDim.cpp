#include "KingSystem/System/AutoDim.h"
#include <nn/oe.h>
#include <prim/seadScopedLock.h>

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(AutoDim)

void AutoDim::setEnabled(bool enable) {
    const auto lock = sead::makeScopedLock(mCS);
    mEnabled = enable;
    if (enable)
        nn::oe::SetUserInactivityDetectionTimeExtended(false);
    else
        nn::oe::SetUserInactivityDetectionTimeExtended(true);
}

bool AutoDim::isEnabled() const {
    return mEnabled;
}

}  // namespace ksys

#include "KingSystem/ksysDebugInput.h"
#include "KingSystem/System/VFR.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(DebugInput)

void DebugInput::update() {
    if (mFlags.isOnBit(0)) {
        mLastDelta += VFR::instance()->getDeltaTime();
        while (mLastDelta > 30.0) {
            mLastDelta -= 30.0;
        }
    }
}

}  // namespace ksys

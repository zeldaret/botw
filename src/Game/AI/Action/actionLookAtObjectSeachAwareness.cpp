#include "Game/AI/Action/actionLookAtObjectSeachAwareness.h"

namespace uking::action {

LookAtObjectSeachAwareness::LookAtObjectSeachAwareness(const InitArg& arg) : LookAtObject(arg) {}

LookAtObjectSeachAwareness::~LookAtObjectSeachAwareness() = default;

bool LookAtObjectSeachAwareness::init_(sead::Heap* heap) {
    return LookAtObject::init_(heap);
}

void LookAtObjectSeachAwareness::loadParams_() {
    LookAtObject::loadParams_();
    getDynamicParam(&mIsRetrySearchBaseProc_d, "IsRetrySearchBaseProc");
}

}  // namespace uking::action

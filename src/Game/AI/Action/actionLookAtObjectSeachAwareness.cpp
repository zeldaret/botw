#include "Game/AI/Action/actionLookAtObjectSeachAwareness.h"

namespace uking::action {

LookAtObjectSeachAwareness::LookAtObjectSeachAwareness(const InitArg& arg) : LookAtObject(arg) {}

LookAtObjectSeachAwareness::~LookAtObjectSeachAwareness() = default;

bool LookAtObjectSeachAwareness::init_(sead::Heap* heap) {
    return LookAtObject::init_(heap);
}

void LookAtObjectSeachAwareness::enter_(ksys::act::ai::InlineParamPack* params) {
    LookAtObject::enter_(params);
}

void LookAtObjectSeachAwareness::leave_() {
    LookAtObject::leave_();
}

void LookAtObjectSeachAwareness::loadParams_() {
    LookAtObject::loadParams_();
    getDynamicParam(&mIsRetrySearchBaseProc_d, "IsRetrySearchBaseProc");
}

void LookAtObjectSeachAwareness::calc_() {
    LookAtObject::calc_();
}

}  // namespace uking::action

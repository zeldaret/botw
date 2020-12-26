#include "Game/AI/Action/actionTurnAndLookToObject.h"

namespace uking::action {

TurnAndLookToObject::TurnAndLookToObject(const InitArg& arg) : LookAtObject(arg) {}

TurnAndLookToObject::~TurnAndLookToObject() = default;

bool TurnAndLookToObject::init_(sead::Heap* heap) {
    return LookAtObject::init_(heap);
}

void TurnAndLookToObject::enter_(ksys::act::ai::InlineParamPack* params) {
    LookAtObject::enter_(params);
}

void TurnAndLookToObject::leave_() {
    LookAtObject::leave_();
}

void TurnAndLookToObject::loadParams_() {
    LookAtObject::loadParams_();
    getDynamicParam(&mIsConfront_d, "IsConfront");
}

void TurnAndLookToObject::calc_() {
    LookAtObject::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionTurnAndLookAtToObjectNow.h"

namespace uking::action {

TurnAndLookAtToObjectNow::TurnAndLookAtToObjectNow(const InitArg& arg) : LookAtObject(arg) {}

TurnAndLookAtToObjectNow::~TurnAndLookAtToObjectNow() = default;

bool TurnAndLookAtToObjectNow::init_(sead::Heap* heap) {
    return LookAtObject::init_(heap);
}

void TurnAndLookAtToObjectNow::enter_(ksys::act::ai::InlineParamPack* params) {
    LookAtObject::enter_(params);
}

void TurnAndLookAtToObjectNow::leave_() {
    LookAtObject::leave_();
}

void TurnAndLookAtToObjectNow::loadParams_() {
    LookAtObject::loadParams_();
    getDynamicParam(&mIsConfront_d, "IsConfront");
}

void TurnAndLookAtToObjectNow::calc_() {
    LookAtObject::calc_();
}

}  // namespace uking::action

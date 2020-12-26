#include "Game/AI/Action/actionFreeMoveToTargetWithBank.h"

namespace uking::action {

FreeMoveToTargetWithBank::FreeMoveToTargetWithBank(const InitArg& arg) : FreeMoveToTarget(arg) {}

FreeMoveToTargetWithBank::~FreeMoveToTargetWithBank() = default;

bool FreeMoveToTargetWithBank::init_(sead::Heap* heap) {
    return FreeMoveToTarget::init_(heap);
}

void FreeMoveToTargetWithBank::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMoveToTarget::enter_(params);
}

void FreeMoveToTargetWithBank::leave_() {
    FreeMoveToTarget::leave_();
}

void FreeMoveToTargetWithBank::loadParams_() {
    FreeMoveToTarget::loadParams_();
    getStaticParam(&mBankAngleMax_s, "BankAngleMax");
    getStaticParam(&mLimitMoveAngle4Bank_s, "LimitMoveAngle4Bank");
}

void FreeMoveToTargetWithBank::calc_() {
    FreeMoveToTarget::calc_();
}

}  // namespace uking::action

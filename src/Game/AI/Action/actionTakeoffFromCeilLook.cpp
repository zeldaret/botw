#include "Game/AI/Action/actionTakeoffFromCeilLook.h"

namespace uking::action {

TakeoffFromCeilLook::TakeoffFromCeilLook(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TakeoffFromCeilLook::~TakeoffFromCeilLook() = default;

bool TakeoffFromCeilLook::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TakeoffFromCeilLook::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TakeoffFromCeilLook::leave_() {
    ksys::act::ai::Action::leave_();
}

void TakeoffFromCeilLook::loadParams_() {
    getStaticParam(&mDescentSpeed_s, "DescentSpeed");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

void TakeoffFromCeilLook::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

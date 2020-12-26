#include "Game/AI/Action/actionDefTurnAction.h"

namespace uking::action {

DefTurnAction::DefTurnAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DefTurnAction::~DefTurnAction() = default;

bool DefTurnAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DefTurnAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DefTurnAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void DefTurnAction::loadParams_() {
    getStaticParam(&mWaitRotate_s, "WaitRotate");
    getStaticParam(&mRotateSpeed_s, "RotateSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DefTurnAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

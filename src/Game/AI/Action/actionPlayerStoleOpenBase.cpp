#include "Game/AI/Action/actionPlayerStoleOpenBase.h"

namespace uking::action {

PlayerStoleOpenBase::PlayerStoleOpenBase(const InitArg& arg) : ActionEx(arg) {}

PlayerStoleOpenBase::~PlayerStoleOpenBase() = default;

void PlayerStoleOpenBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void PlayerStoleOpenBase::leave_() {
    ActionEx::leave_();
}

void PlayerStoleOpenBase::loadParams_() {
    getStaticParam(&mBoneName_s, "BoneName");
    getStaticParam(&mPosOffset_s, "PosOffset");
    getStaticParam(&mRotOffsetXyz_s, "RotOffsetXyz");
}

void PlayerStoleOpenBase::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action

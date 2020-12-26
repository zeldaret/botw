#include "Game/AI/Action/actionPlayerStoleOpenEx.h"

namespace uking::action {

PlayerStoleOpenEx::PlayerStoleOpenEx(const InitArg& arg) : PlayerStoleOpenBase(arg) {}

PlayerStoleOpenEx::~PlayerStoleOpenEx() = default;

bool PlayerStoleOpenEx::init_(sead::Heap* heap) {
    return PlayerStoleOpenBase::init_(heap);
}

void PlayerStoleOpenEx::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerStoleOpenBase::enter_(params);
}

void PlayerStoleOpenEx::leave_() {
    PlayerStoleOpenBase::leave_();
}

void PlayerStoleOpenEx::loadParams_() {
    getStaticParam(&mBoneName_s, "BoneName");
    getStaticParam(&mPosOffset_s, "PosOffset");
    getStaticParam(&mRotOffsetXyz_s, "RotOffsetXyz");
}

void PlayerStoleOpenEx::calc_() {
    PlayerStoleOpenBase::calc_();
}

}  // namespace uking::action

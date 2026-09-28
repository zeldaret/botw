#include "Game/Actor/Action/actionWillBallAttack.h"

namespace uking::action {

WillBallAttack::WillBallAttack(const InitArg& arg) : WillBallBase(arg) {}

WillBallAttack::~WillBallAttack() = default;

bool WillBallAttack::init_(sead::Heap* heap) {
    return WillBallBase::init_(heap);
}

void WillBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    WillBallBase::enter_(params);
}

void WillBallAttack::leave_() {
    WillBallBase::leave_();
}

void WillBallAttack::loadParams_() {
    WillBallBase::loadParams_();
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mIsAbleGuard_s, "IsAbleGuard");
}

void WillBallAttack::calc_() {
    WillBallBase::calc_();
}

}  // namespace uking::action

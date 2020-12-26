#include "Game/AI/Action/actionWillBallAttack.h"

namespace uking::action {

WillBallAttack::WillBallAttack(const InitArg& arg) : WillBallAction(arg) {}

WillBallAttack::~WillBallAttack() = default;

bool WillBallAttack::init_(sead::Heap* heap) {
    return WillBallAction::init_(heap);
}

void WillBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    WillBallAction::enter_(params);
}

void WillBallAttack::leave_() {
    WillBallAction::leave_();
}

void WillBallAttack::loadParams_() {
    WillBallAction::loadParams_();
    getStaticParam(&mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mIsAbleGuard_s, "IsAbleGuard");
}

void WillBallAttack::calc_() {
    WillBallAction::calc_();
}

}  // namespace uking::action

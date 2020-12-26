#include "Game/AI/Action/actionDemoApplyDamageForPlayer.h"

namespace uking::action {

DemoApplyDamageForPlayer::DemoApplyDamageForPlayer(const InitArg& arg)
    : ApplyDamageForPlayer(arg) {}

DemoApplyDamageForPlayer::~DemoApplyDamageForPlayer() = default;

bool DemoApplyDamageForPlayer::init_(sead::Heap* heap) {
    return ApplyDamageForPlayer::init_(heap);
}

void DemoApplyDamageForPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ApplyDamageForPlayer::enter_(params);
}

void DemoApplyDamageForPlayer::leave_() {
    ApplyDamageForPlayer::leave_();
}

void DemoApplyDamageForPlayer::loadParams_() {
    ApplyDamageForPlayer::loadParams_();
}

void DemoApplyDamageForPlayer::calc_() {
    ApplyDamageForPlayer::calc_();
}

}  // namespace uking::action

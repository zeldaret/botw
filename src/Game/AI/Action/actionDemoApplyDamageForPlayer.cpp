#include "Game/AI/Action/actionDemoApplyDamageForPlayer.h"

namespace uking::action {

DemoApplyDamageForPlayer::DemoApplyDamageForPlayer(const InitArg& arg)
    : ApplyDamageForPlayer(arg) {}

DemoApplyDamageForPlayer::~DemoApplyDamageForPlayer() = default;

bool DemoApplyDamageForPlayer::init_(sead::Heap* heap) {
    return ApplyDamageForPlayer::init_(heap);
}

void DemoApplyDamageForPlayer::loadParams_() {
    ApplyDamageForPlayer::loadParams_();
}

}  // namespace uking::action

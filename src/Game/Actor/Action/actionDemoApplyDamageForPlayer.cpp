#include "Game/Actor/Action/actionDemoApplyDamageForPlayer.h"

namespace uking::action {

DemoApplyDamageForPlayer::DemoApplyDamageForPlayer(const InitArg& arg) : DemoApplyDamageBase(arg) {}

DemoApplyDamageForPlayer::~DemoApplyDamageForPlayer() = default;

bool DemoApplyDamageForPlayer::init_(sead::Heap* heap) {
    return DemoApplyDamageBase::init_(heap);
}

void DemoApplyDamageForPlayer::loadParams_() {
    DemoApplyDamageBase::loadParams_();
}

}  // namespace uking::action

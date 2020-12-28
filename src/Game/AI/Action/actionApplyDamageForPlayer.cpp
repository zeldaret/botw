#include "Game/AI/Action/actionApplyDamageForPlayer.h"

namespace uking::action {

ApplyDamageForPlayer::ApplyDamageForPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ApplyDamageForPlayer::~ApplyDamageForPlayer() = default;

bool ApplyDamageForPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ApplyDamageForPlayer::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action

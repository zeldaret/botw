#include "Game/AI/Action/actionApplyDamageForPlayer.h"

namespace uking::action {

ApplyDamageForPlayer::ApplyDamageForPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ApplyDamageForPlayer::~ApplyDamageForPlayer() = default;

bool ApplyDamageForPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ApplyDamageForPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ApplyDamageForPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void ApplyDamageForPlayer::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

void ApplyDamageForPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

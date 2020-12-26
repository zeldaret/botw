#include "Game/AI/Action/actionForceSetMtxFromPlayer.h"

namespace uking::action {

ForceSetMtxFromPlayer::ForceSetMtxFromPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceSetMtxFromPlayer::~ForceSetMtxFromPlayer() = default;

bool ForceSetMtxFromPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceSetMtxFromPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceSetMtxFromPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceSetMtxFromPlayer::loadParams_() {}

void ForceSetMtxFromPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

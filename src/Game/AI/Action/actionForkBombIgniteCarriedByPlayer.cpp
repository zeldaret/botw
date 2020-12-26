#include "Game/AI/Action/actionForkBombIgniteCarriedByPlayer.h"

namespace uking::action {

ForkBombIgniteCarriedByPlayer::ForkBombIgniteCarriedByPlayer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkBombIgniteCarriedByPlayer::~ForkBombIgniteCarriedByPlayer() = default;

bool ForkBombIgniteCarriedByPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkBombIgniteCarriedByPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkBombIgniteCarriedByPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkBombIgniteCarriedByPlayer::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getAITreeVariable(&mIsIgniteCarriedBomb_a, "IsIgniteCarriedBomb");
}

void ForkBombIgniteCarriedByPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

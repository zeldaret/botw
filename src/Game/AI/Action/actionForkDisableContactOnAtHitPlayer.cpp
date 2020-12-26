#include "Game/AI/Action/actionForkDisableContactOnAtHitPlayer.h"

namespace uking::action {

ForkDisableContactOnAtHitPlayer::ForkDisableContactOnAtHitPlayer(const InitArg& arg)
    : ForkDisableContact(arg) {}

ForkDisableContactOnAtHitPlayer::~ForkDisableContactOnAtHitPlayer() = default;

bool ForkDisableContactOnAtHitPlayer::init_(sead::Heap* heap) {
    return ForkDisableContact::init_(heap);
}

void ForkDisableContactOnAtHitPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDisableContact::enter_(params);
}

void ForkDisableContactOnAtHitPlayer::leave_() {
    ForkDisableContact::leave_();
}

void ForkDisableContactOnAtHitPlayer::loadParams_() {
    ForkDisableContact::loadParams_();
}

void ForkDisableContactOnAtHitPlayer::calc_() {
    ForkDisableContact::calc_();
}

}  // namespace uking::action

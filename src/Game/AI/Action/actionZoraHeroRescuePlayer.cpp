#include "Game/AI/Action/actionZoraHeroRescuePlayer.h"

namespace uking::action {

ZoraHeroRescuePlayer::ZoraHeroRescuePlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ZoraHeroRescuePlayer::~ZoraHeroRescuePlayer() = default;

bool ZoraHeroRescuePlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ZoraHeroRescuePlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ZoraHeroRescuePlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void ZoraHeroRescuePlayer::loadParams_() {
    getAITreeVariable(&mZoraHeroShowMsgUnit_a, "ZoraHeroShowMsgUnit");
}

void ZoraHeroRescuePlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

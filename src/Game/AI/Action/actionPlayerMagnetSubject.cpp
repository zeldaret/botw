#include "Game/AI/Action/actionPlayerMagnetSubject.h"

namespace uking::action {

PlayerMagnetSubject::PlayerMagnetSubject(const InitArg& arg) : PlayerAction(arg) {}

void PlayerMagnetSubject::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerMagnetSubject::leave_() {
    PlayerAction::leave_();
}

void PlayerMagnetSubject::loadParams_() {
    getStaticParam(&mDRCEnergy_s, "DRCEnergy");
}

void PlayerMagnetSubject::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionPlayerGuardSlip.h"

namespace uking::action {

PlayerGuardSlip::PlayerGuardSlip(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuardSlip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGuardSlip::leave_() {
    PlayerAction::leave_();
}

void PlayerGuardSlip::loadParams_() {
    getStaticParam(&mBaseInitSpeedNSword_s, "BaseInitSpeedNSword");
    getStaticParam(&mBaseInitSpeedLSword_s, "BaseInitSpeedLSword");
    getStaticParam(&mBaseInitSpeedSpear_s, "BaseInitSpeedSpear");
    getStaticParam(&mBaseInitSpeedOther_s, "BaseInitSpeedOther");
    getStaticParam(&mAddSpeedNSword_s, "AddSpeedNSword");
    getStaticParam(&mAddSpeedLSword_s, "AddSpeedLSword");
    getStaticParam(&mAddSpeedSpear_s, "AddSpeedSpear");
    getStaticParam(&mAddSpeedOther_s, "AddSpeedOther");
    getStaticParam(&mMaxSpeedNSword_s, "MaxSpeedNSword");
    getStaticParam(&mMaxSpeedLSword_s, "MaxSpeedLSword");
    getStaticParam(&mMaxSpeedSpear_s, "MaxSpeedSpear");
    getStaticParam(&mMaxSpeedOther_s, "MaxSpeedOther");
    getStaticParam(&mDecSpeedNSword_s, "DecSpeedNSword");
    getStaticParam(&mDecSpeedLSword_s, "DecSpeedLSword");
    getStaticParam(&mDecSpeedSpear_s, "DecSpeedSpear");
    getStaticParam(&mDecSpeedOther_s, "DecSpeedOther");
}

void PlayerGuardSlip::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action

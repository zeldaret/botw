#include "Game/AI/Action/actionPlayerLargeDamage.h"

namespace uking::action {

PlayerLargeDamage::PlayerLargeDamage(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLargeDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLargeDamage::leave_() {
    PlayerAction::leave_();
}

void PlayerLargeDamage::loadParams_() {
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
    getStaticParam(&mJumpHeightNSword_s, "JumpHeightNSword");
    getStaticParam(&mJumpHeightLSword_s, "JumpHeightLSword");
    getStaticParam(&mJumpHeightSpear_s, "JumpHeightSpear");
    getStaticParam(&mJumpHeightOther_s, "JumpHeightOther");
    getStaticParam(&mInitSpeedWind_s, "InitSpeedWind");
    getStaticParam(&mJumpHeightWind_s, "JumpHeightWind");
    getStaticParam(&mNoRagdollTime_s, "NoRagdollTime");
    getStaticParam(&mInitSpeedToss_s, "InitSpeedToss");
    getStaticParam(&mJumpHeightToss_s, "JumpHeightToss");
    getStaticParam(&mAddLinearImpulse_s, "AddLinearImpulse");
    getStaticParam(&mAddRollImpulse_s, "AddRollImpulse");
    getStaticParam(&mInitSpeedHorse_s, "InitSpeedHorse");
    getStaticParam(&mJumpHeightHorse_s, "JumpHeightHorse");
    getStaticParam(&mAddLinearImpulseHorse_s, "AddLinearImpulseHorse");
    getStaticParam(&mInitSpeedRynel_s, "InitSpeedRynel");
    getStaticParam(&mJumpHeightRynel_s, "JumpHeightRynel");
    getStaticParam(&mAddLinearImpulseRynel_s, "AddLinearImpulseRynel");
    getStaticParam(&mAddRollImpulseRynel_s, "AddRollImpulseRynel");
    getStaticParam(&mInitSpeedSandworm_s, "InitSpeedSandworm");
    getStaticParam(&mJumpHeightSandworm_s, "JumpHeightSandworm");
    getStaticParam(&mAddLinearImpulseSandworm_s, "AddLinearImpulseSandworm");
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
    getStaticParam(&mJumpHeightNSword_s, "JumpHeightNSword");
    getStaticParam(&mJumpHeightLSword_s, "JumpHeightLSword");
    getStaticParam(&mJumpHeightSpear_s, "JumpHeightSpear");
    getStaticParam(&mJumpHeightOther_s, "JumpHeightOther");
    getStaticParam(&mInitSpeedWind_s, "InitSpeedWind");
    getStaticParam(&mJumpHeightWind_s, "JumpHeightWind");
    getStaticParam(&mNoRagdollTime_s, "NoRagdollTime");
    getStaticParam(&mInitSpeedToss_s, "InitSpeedToss");
    getStaticParam(&mJumpHeightToss_s, "JumpHeightToss");
    getStaticParam(&mAddLinearImpulse_s, "AddLinearImpulse");
    getStaticParam(&mAddRollImpulse_s, "AddRollImpulse");
    getStaticParam(&mInitSpeedHorse_s, "InitSpeedHorse");
    getStaticParam(&mJumpHeightHorse_s, "JumpHeightHorse");
    getStaticParam(&mAddLinearImpulseHorse_s, "AddLinearImpulseHorse");
    getStaticParam(&mInitSpeedRynel_s, "InitSpeedRynel");
    getStaticParam(&mJumpHeightRynel_s, "JumpHeightRynel");
    getStaticParam(&mAddLinearImpulseRynel_s, "AddLinearImpulseRynel");
    getStaticParam(&mAddRollImpulseRynel_s, "AddRollImpulseRynel");
    getStaticParam(&mInitSpeedSandworm_s, "InitSpeedSandworm");
    getStaticParam(&mJumpHeightSandworm_s, "JumpHeightSandworm");
    getStaticParam(&mAddLinearImpulseSandworm_s, "AddLinearImpulseSandworm");
    getStaticParam(&mInitSpeedShakeOff_s, "InitSpeedShakeOff");
    getStaticParam(&mJumpHeightShakeOff_s, "JumpHeightShakeOff");
    getStaticParam(&mAddLinearImpulseShakeOff_s, "AddLinearImpulseShakeOff");
    getStaticParam(&mInitSpeedWindRemain_s, "InitSpeedWindRemain");
    getStaticParam(&mJumpHeightWindRemain_s, "JumpHeightWindRemain");
    getStaticParam(&mAddLinearImpulseWindRemain_s, "AddLinearImpulseWindRemain");
}

void PlayerLargeDamage::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action

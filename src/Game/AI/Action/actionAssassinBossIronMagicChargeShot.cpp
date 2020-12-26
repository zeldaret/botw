#include "Game/AI/Action/actionAssassinBossIronMagicChargeShot.h"

namespace uking::action {

AssassinBossIronMagicChargeShot::AssassinBossIronMagicChargeShot(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AssassinBossIronMagicChargeShot::~AssassinBossIronMagicChargeShot() = default;

bool AssassinBossIronMagicChargeShot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AssassinBossIronMagicChargeShot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AssassinBossIronMagicChargeShot::leave_() {
    ksys::act::ai::Action::leave_();
}

void AssassinBossIronMagicChargeShot::loadParams_() {
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mIronBallPartsName_s, "IronBallPartsName");
    getStaticParam(&mLevel2AttackLifeRatio_s, "Level2AttackLifeRatio");
}

void AssassinBossIronMagicChargeShot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionAssassinBossIronBallAttack.h"

namespace uking::action {

AssassinBossIronBallAttack::AssassinBossIronBallAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AssassinBossIronBallAttack::~AssassinBossIronBallAttack() = default;

bool AssassinBossIronBallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AssassinBossIronBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AssassinBossIronBallAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void AssassinBossIronBallAttack::loadParams_() {
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mIronBallPartsName_s, "IronBallPartsName");
}

void AssassinBossIronBallAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

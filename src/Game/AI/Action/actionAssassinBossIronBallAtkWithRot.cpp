#include "Game/AI/Action/actionAssassinBossIronBallAtkWithRot.h"

namespace uking::action {

AssassinBossIronBallAtkWithRot::AssassinBossIronBallAtkWithRot(const InitArg& arg)
    : AssassinBossIronBallAttack(arg) {}

AssassinBossIronBallAtkWithRot::~AssassinBossIronBallAtkWithRot() = default;

bool AssassinBossIronBallAtkWithRot::init_(sead::Heap* heap) {
    return AssassinBossIronBallAttack::init_(heap);
}

void AssassinBossIronBallAtkWithRot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinBossIronBallAttack::enter_(params);
}

void AssassinBossIronBallAtkWithRot::leave_() {
    AssassinBossIronBallAttack::leave_();
}

void AssassinBossIronBallAtkWithRot::loadParams_() {
    AssassinBossIronBallAttack::loadParams_();
    getStaticParam(&mAddAngle_s, "AddAngle");
    getStaticParam(&mCentralAnchorName_s, "CentralAnchorName");
}

void AssassinBossIronBallAtkWithRot::calc_() {
    AssassinBossIronBallAttack::calc_();
}

}  // namespace uking::action

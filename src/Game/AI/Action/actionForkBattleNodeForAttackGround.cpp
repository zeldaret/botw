#include "Game/AI/Action/actionForkBattleNodeForAttackGround.h"

namespace uking::action {

ForkBattleNodeForAttackGround::ForkBattleNodeForAttackGround(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkBattleNodeForAttackGround::~ForkBattleNodeForAttackGround() = default;

bool ForkBattleNodeForAttackGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkBattleNodeForAttackGround::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkBattleNodeForAttackGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkBattleNodeForAttackGround::loadParams_() {
    getStaticParam(&mIsOffsetFromBaseBone_s, "IsOffsetFromBaseBone");
    getStaticParam(&mAttackPosOffset_s, "AttackPosOffset");
}

void ForkBattleNodeForAttackGround::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

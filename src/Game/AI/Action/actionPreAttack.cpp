#include "Game/AI/Action/actionPreAttack.h"

namespace uking::action {

PreAttack::PreAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PreAttack::~PreAttack() = default;

bool PreAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PreAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void PreAttack::loadParams_() {
    getStaticParam(&mTurnSpd_s, "TurnSpd");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void PreAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

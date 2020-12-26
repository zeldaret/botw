#include "Game/AI/Action/actionLyzalfosFlame.h"

namespace uking::action {

LyzalfosFlame::LyzalfosFlame(const InitArg& arg) : ChemicalAttackBall(arg) {}

LyzalfosFlame::~LyzalfosFlame() = default;

bool LyzalfosFlame::init_(sead::Heap* heap) {
    return ChemicalAttackBall::init_(heap);
}

void LyzalfosFlame::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttackBall::enter_(params);
}

void LyzalfosFlame::leave_() {
    ChemicalAttackBall::leave_();
}

void LyzalfosFlame::loadParams_() {
    ChemicalAttackBall::loadParams_();
    getStaticParam(&mLengthFrame_s, "LengthFrame");
    getStaticParam(&mAtResetTime_s, "AtResetTime");
    getStaticParam(&mAtChaseFrame_s, "AtChaseFrame");
    getStaticParam(&mBindGrabNodeIdx_s, "BindGrabNodeIdx");
    getStaticParam(&mChaseMax_s, "ChaseMax");
    getStaticParam(&mChaseRate_s, "ChaseRate");
    getStaticParam(&mOffsetRot_s, "OffsetRot");
}

void LyzalfosFlame::calc_() {
    ChemicalAttackBall::calc_();
}

}  // namespace uking::action

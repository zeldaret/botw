#include "Game/Actor/Action/actionLyzalfosFlame.h"

namespace uking::action {

LyzalfosFlame::LyzalfosFlame(const InitArg& arg) : ChemicalAttack(arg) {}

LyzalfosFlame::~LyzalfosFlame() = default;

bool LyzalfosFlame::init_(sead::Heap* heap) {
    return ChemicalAttack::init_(heap);
}

void LyzalfosFlame::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttack::enter_(params);
}

void LyzalfosFlame::leave_() {
    ChemicalAttack::leave_();
}

void LyzalfosFlame::loadParams_() {
    ChemicalAttack::loadParams_();
    getStaticParam(&mLengthFrame_s, "LengthFrame");
    getStaticParam(&mAtResetTime_s, "AtResetTime");
    getStaticParam(&mAtChaseFrame_s, "AtChaseFrame");
    getStaticParam(&mBindGrabNodeIdx_s, "BindGrabNodeIdx");
    getStaticParam(&mChaseMax_s, "ChaseMax");
    getStaticParam(&mChaseRate_s, "ChaseRate");
    getStaticParam(&mOffsetRot_s, "OffsetRot");
}

void LyzalfosFlame::calc_() {
    ChemicalAttack::calc_();
}

}  // namespace uking::action

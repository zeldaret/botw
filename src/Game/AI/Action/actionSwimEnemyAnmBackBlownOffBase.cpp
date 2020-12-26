#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOffBase.h"

namespace uking::action {

SwimEnemyAnmBackBlownOffBase::SwimEnemyAnmBackBlownOffBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SwimEnemyAnmBackBlownOffBase::~SwimEnemyAnmBackBlownOffBase() = default;

bool SwimEnemyAnmBackBlownOffBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwimEnemyAnmBackBlownOffBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwimEnemyAnmBackBlownOffBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwimEnemyAnmBackBlownOffBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mBlownHeight_s, "BlownHeight");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mUseKnockbackDir_s, "UseKnockbackDir");
    getStaticParam(&mAS_s, "AS");
}

void SwimEnemyAnmBackBlownOffBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

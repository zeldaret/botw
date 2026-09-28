#include "Game/Actor/Action/actionSwimEnemyBlownOffBase.h"

namespace uking::action {

SwimEnemyBlownOffBase::SwimEnemyBlownOffBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwimEnemyBlownOffBase::~SwimEnemyBlownOffBase() = default;

bool SwimEnemyBlownOffBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwimEnemyBlownOffBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwimEnemyBlownOffBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwimEnemyBlownOffBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mBlownHeight_s, "BlownHeight");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mUseKnockbackDir_s, "UseKnockbackDir");
    getStaticParam(&mAS_s, "AS");
}

void SwimEnemyBlownOffBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

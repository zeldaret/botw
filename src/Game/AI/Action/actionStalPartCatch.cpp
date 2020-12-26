#include "Game/AI/Action/actionStalPartCatch.h"

namespace uking::action {

StalPartCatch::StalPartCatch(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StalPartCatch::~StalPartCatch() = default;

bool StalPartCatch::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StalPartCatch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StalPartCatch::leave_() {
    ksys::act::ai::Action::leave_();
}

void StalPartCatch::loadParams_() {
    getStaticParam(&mPartIndex_s, "PartIndex");
    getStaticParam(&mInputWeightTimer_s, "InputWeightTimer");
    getStaticParam(&mBlendWeightTimer_s, "BlendWeightTimer");
    getStaticParam(&mBaseRagdollRigidBodyName_s, "BaseRagdollRigidBodyName");
    getStaticParam(&mSecondRagdollRigidBodyName_s, "SecondRagdollRigidBodyName");
    getStaticParam(&mThirdRagdollRigidBodyName_s, "ThirdRagdollRigidBodyName");
    getStaticParam(&mConstraintNames_s, "ConstraintNames");
    getStaticParam(&mFreeMoveRagdollRigidBodyNames_s, "FreeMoveRagdollRigidBodyNames");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mUseRagConName_s, "UseRagConName");
    getStaticParam(&mUnitePosOffset_s, "UnitePosOffset");
    getStaticParam(&mUniteRotOffset_s, "UniteRotOffset");
    getStaticParam(&mSecondUnitePosOffset_s, "SecondUnitePosOffset");
    getStaticParam(&mSecondUniteRotOffset_s, "SecondUniteRotOffset");
    getStaticParam(&mThirdUnitePosOffset_s, "ThirdUnitePosOffset");
    getStaticParam(&mThirdUniteRotOffset_s, "ThirdUniteRotOffset");
}

void StalPartCatch::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

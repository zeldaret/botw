#include "Game/AI/Action/actionForkEmitExpandField.h"

namespace uking::action {

ForkEmitExpandField::ForkEmitExpandField(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkEmitExpandField::~ForkEmitExpandField() = default;

bool ForkEmitExpandField::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkEmitExpandField::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkEmitExpandField::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkEmitExpandField::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mCutGrassType_s, "CutGrassType");
    getStaticParam(&mAtTarget_s, "AtTarget");
    getStaticParam(&mScale_s, "Scale");
    getStaticParam(&mActorPowerScale_s, "ActorPowerScale");
    getStaticParam(&mIsUseAtCollision_s, "IsUseAtCollision");
    getStaticParam(&mPartsKey_s, "PartsKey");
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getStaticParam(&mAtDirType_s, "AtDirType");
}

void ForkEmitExpandField::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/Actor/Action/actionStalEnemyHeadShotReaction.h"

namespace uking::action {

StalEnemyHeadShotReaction::StalEnemyHeadShotReaction(const InitArg& arg) : StopBase(arg) {}

StalEnemyHeadShotReaction::~StalEnemyHeadShotReaction() = default;

bool StalEnemyHeadShotReaction::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void StalEnemyHeadShotReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void StalEnemyHeadShotReaction::leave_() {
    StopBase::leave_();
}

void StalEnemyHeadShotReaction::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mUseAddVec_s, "UseAddVec");
    getStaticParam(&mIsTgOff_s, "IsTgOff");
    getStaticParam(&mIsDropWeapon_s, "IsDropWeapon");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mHeadBoneKey_s, "HeadBoneKey");
    getStaticParam(&mAddVec_s, "AddVec");
    getStaticParam(&mRotVec_s, "RotVec");
}

void StalEnemyHeadShotReaction::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action

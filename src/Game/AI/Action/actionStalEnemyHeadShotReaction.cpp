#include "Game/AI/Action/actionStalEnemyHeadShotReaction.h"

namespace uking::action {

StalEnemyHeadShotReaction::StalEnemyHeadShotReaction(const InitArg& arg)
    : ActionWithPosAngReduce(arg) {}

StalEnemyHeadShotReaction::~StalEnemyHeadShotReaction() = default;

bool StalEnemyHeadShotReaction::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void StalEnemyHeadShotReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void StalEnemyHeadShotReaction::leave_() {
    ActionWithPosAngReduce::leave_();
}

void StalEnemyHeadShotReaction::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
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
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action

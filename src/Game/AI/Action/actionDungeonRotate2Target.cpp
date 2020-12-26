#include "Game/AI/Action/actionDungeonRotate2Target.h"

namespace uking::action {

DungeonRotate2Target::DungeonRotate2Target(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotate2Target::~DungeonRotate2Target() = default;

bool DungeonRotate2Target::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotate2Target::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
}

void DungeonRotate2Target::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotate2Target::loadParams_() {
    DungeonRotateBase::loadParams_();
    getStaticParam(&mDgnRotDir_s, "DgnRotDir");
    getStaticParam(&mRotSpAccel_s, "RotSpAccel");
    getStaticParam(&mRotSpSlowDown_s, "RotSpSlowDown");
    getStaticParam(&mRotSpSlowDownTh_s, "RotSpSlowDownTh");
    getStaticParam(&mMinRotSp_s, "MinRotSp");
    getStaticParam(&mRotReverseSlowDown_s, "RotReverseSlowDown");
    getAITreeVariable(&mTargetRad_a, "TargetRad");
    getAITreeVariable(&mTargetRadMax_a, "TargetRadMax");
    getAITreeVariable(&mTargetRadMin_a, "TargetRadMin");
}

void DungeonRotate2Target::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action

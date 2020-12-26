#include "Game/AI/Action/actionBowChildReflectBullet.h"

namespace uking::action {

BowChildReflectBullet::BowChildReflectBullet(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildReflectBullet::~BowChildReflectBullet() = default;

bool BowChildReflectBullet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildReflectBullet::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BowChildReflectBullet::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildReflectBullet::loadParams_() {
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mOffsetLength_s, "OffsetLength");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mTargetMoveOffset_s, "TargetMoveOffset");
    getStaticParam(&mTargetMoveOffsetRandRange_s, "TargetMoveOffsetRandRange");
    getStaticParam(&mMoveRotateRate_s, "MoveRotateRate");
    getStaticParam(&mMoveRotateMax_s, "MoveRotateMax");
    getStaticParam(&mMoveRotateMin_s, "MoveRotateMin");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mIsReflectAmongChild_d, "IsReflectAmongChild");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildReflectBullet::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

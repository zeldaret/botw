#include "Game/AI/Action/actionDungeonRotateAccel.h"

namespace uking::action {

DungeonRotateAccel::DungeonRotateAccel(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotateAccel::~DungeonRotateAccel() = default;

bool DungeonRotateAccel::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotateAccel::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
}

void DungeonRotateAccel::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotateAccel::loadParams_() {
    DungeonRotateBase::loadParams_();
    getStaticParam(&mIsSlowDown_s, "IsSlowDown");
    getDynamicParam(&mDynCurrentAngVel_d, "DynCurrentAngVel");
    getDynamicParam(&mDynAngAccel_d, "DynAngAccel");
}

void DungeonRotateAccel::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action

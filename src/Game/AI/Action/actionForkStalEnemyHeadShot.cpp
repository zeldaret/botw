#include "Game/AI/Action/actionForkStalEnemyHeadShot.h"

namespace uking::action {

ForkStalEnemyHeadShot::ForkStalEnemyHeadShot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkStalEnemyHeadShot::~ForkStalEnemyHeadShot() = default;

bool ForkStalEnemyHeadShot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStalEnemyHeadShot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkStalEnemyHeadShot::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkStalEnemyHeadShot::loadParams_() {
    getStaticParam(&mVisibleCount_s, "VisibleCount");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mUseAddVec_s, "UseAddVec");
    getStaticParam(&mHeadBoneKey_s, "HeadBoneKey");
    getStaticParam(&mAddVec_s, "AddVec");
    getStaticParam(&mRotVec_s, "RotVec");
}

void ForkStalEnemyHeadShot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

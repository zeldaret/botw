#include "Game/AI/AI/aiRangeObstacleCheck.h"

namespace uking::ai {

RangeObstacleCheck::RangeObstacleCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RangeObstacleCheck::~RangeObstacleCheck() = default;

bool RangeObstacleCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RangeObstacleCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RangeObstacleCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RangeObstacleCheck::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRangeDist_s, "RangeDist");
    getStaticParam(&mHeightMin_s, "HeightMin");
    getStaticParam(&mHeightMax_s, "HeightMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

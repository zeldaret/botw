#include "Game/AI/AI/aiNPCAvoid.h"

namespace uking::ai {

NPCAvoid::NPCAvoid(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAvoid::~NPCAvoid() = default;

void NPCAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCAvoid::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCAvoid::loadParams_() {
    getStaticParam(&mTargetTerrorLevel_s, "TargetTerrorLevel");
    getStaticParam(&mReleaseCrouchTime_s, "ReleaseCrouchTime");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mIsSitting_d, "IsSitting");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai

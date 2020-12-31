#include "Game/AI/AI/aiNPCTerrorAI.h"

namespace uking::ai {

NPCTerrorAI::NPCTerrorAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCTerrorAI::~NPCTerrorAI() = default;

void NPCTerrorAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCTerrorAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCTerrorAI::loadParams_() {
    getStaticParam(&mTerrorEndTime_s, "TerrorEndTime");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mIsTimeOver_d, "IsTimeOver");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai

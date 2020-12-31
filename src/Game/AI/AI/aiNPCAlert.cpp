#include "Game/AI/AI/aiNPCAlert.h"

namespace uking::ai {

NPCAlert::NPCAlert(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAlert::~NPCAlert() = default;

bool NPCAlert::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCAlert::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCAlert::loadParams_() {
    getStaticParam(&mMinReactionTime_s, "MinReactionTime");
    getStaticParam(&mReleaseDist_s, "ReleaseDist");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mIsTimeOver_d, "IsTimeOver");
    getDynamicParam(&mIsSitting_d, "IsSitting");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai

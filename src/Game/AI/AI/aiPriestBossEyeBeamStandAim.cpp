#include "Game/AI/AI/aiPriestBossEyeBeamStandAim.h"

namespace uking::ai {

PriestBossEyeBeamStandAim::PriestBossEyeBeamStandAim(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossEyeBeamStandAim::~PriestBossEyeBeamStandAim() = default;

bool PriestBossEyeBeamStandAim::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossEyeBeamStandAim::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossEyeBeamStandAim::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossEyeBeamStandAim::loadParams_() {
    getStaticParam(&mBorderDist_s, "BorderDist");
    getStaticParam(&mBorderHeight_s, "BorderHeight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAimTargetPos_d, "AimTargetPos");
}

}  // namespace uking::ai

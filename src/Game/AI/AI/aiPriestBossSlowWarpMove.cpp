#include "Game/AI/AI/aiPriestBossSlowWarpMove.h"

namespace uking::ai {

PriestBossSlowWarpMove::PriestBossSlowWarpMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossSlowWarpMove::~PriestBossSlowWarpMove() = default;

bool PriestBossSlowWarpMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossSlowWarpMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossSlowWarpMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossSlowWarpMove::loadParams_() {
    getStaticParam(&mAfterImage0AppearFrame_s, "AfterImage0AppearFrame");
    getStaticParam(&mAfterImage1AppearFrame_s, "AfterImage1AppearFrame");
    getStaticParam(&mAppearFrame_s, "AppearFrame");
    getStaticParam(&mTurnFirst_s, "TurnFirst");
    getDynamicParam(&mCurrentFrame_d, "CurrentFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
    getDynamicParam(&mAfterImage0Pos_d, "AfterImage0Pos");
    getDynamicParam(&mAfterImage1Pos_d, "AfterImage1Pos");
}

}  // namespace uking::ai

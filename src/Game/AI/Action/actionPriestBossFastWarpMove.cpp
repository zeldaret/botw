#include "Game/AI/Action/actionPriestBossFastWarpMove.h"

namespace uking::action {

PriestBossFastWarpMove::PriestBossFastWarpMove(const InitArg& arg) : PriestBossWarpOrVanish(arg) {}

PriestBossFastWarpMove::~PriestBossFastWarpMove() = default;

bool PriestBossFastWarpMove::init_(sead::Heap* heap) {
    return PriestBossWarpOrVanish::init_(heap);
}

void PriestBossFastWarpMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossWarpOrVanish::enter_(params);
}

void PriestBossFastWarpMove::leave_() {
    PriestBossWarpOrVanish::leave_();
}

void PriestBossFastWarpMove::loadParams_() {
    PriestBossWarpOrVanish::loadParams_();
    getStaticParam(&mAfterImage0AppearFrame_s, "AfterImage0AppearFrame");
    getStaticParam(&mAfterImage1AppearFrame_s, "AfterImage1AppearFrame");
    getStaticParam(&mAppearFrame_s, "AppearFrame");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mCurrentFrame_d, "CurrentFrame");
    getDynamicParam(&mIsCloseMove_d, "IsCloseMove");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
    getDynamicParam(&mAfterImage0Pos_d, "AfterImage0Pos");
    getDynamicParam(&mAfterImage1Pos_d, "AfterImage1Pos");
}

void PriestBossFastWarpMove::calc_() {
    PriestBossWarpOrVanish::calc_();
}

}  // namespace uking::action

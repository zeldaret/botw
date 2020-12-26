#include "Game/AI/Action/actionSandwormNavMove.h"

namespace uking::action {

SandwormNavMove::SandwormNavMove(const InitArg& arg) : NavMeshMoveWithAS(arg) {}

SandwormNavMove::~SandwormNavMove() = default;

bool SandwormNavMove::init_(sead::Heap* heap) {
    return NavMeshMoveWithAS::init_(heap);
}

void SandwormNavMove::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshMoveWithAS::enter_(params);
}

void SandwormNavMove::leave_() {
    NavMeshMoveWithAS::leave_();
}

void SandwormNavMove::loadParams_() {
    NavMeshMoveWithAS::loadParams_();
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void SandwormNavMove::calc_() {
    NavMeshMoveWithAS::calc_();
}

}  // namespace uking::action

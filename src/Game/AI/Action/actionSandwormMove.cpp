#include "Game/AI/Action/actionSandwormMove.h"

namespace uking::action {

SandwormMove::SandwormMove(const InitArg& arg) : MoveWithAS(arg) {}

SandwormMove::~SandwormMove() = default;

bool SandwormMove::init_(sead::Heap* heap) {
    return MoveWithAS::init_(heap);
}

void SandwormMove::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveWithAS::enter_(params);
}

void SandwormMove::leave_() {
    MoveWithAS::leave_();
}

void SandwormMove::loadParams_() {
    MoveWithAS::loadParams_();
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getStaticParam(&mIsCheckAnmSeqCancel_s, "IsCheckAnmSeqCancel");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void SandwormMove::calc_() {
    MoveWithAS::calc_();
}

}  // namespace uking::action

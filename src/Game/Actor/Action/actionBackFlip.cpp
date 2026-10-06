#include "Game/Actor/Action/actionBackFlip.h"

namespace uking::action {

BackFlip::BackFlip(const InitArg& arg) : ASPlayRotateTurnToTarget(arg) {}

BackFlip::~BackFlip() = default;

bool BackFlip::init_(sead::Heap* heap) {
    return ASPlayRotateTurnToTarget::init_(heap);
}

void BackFlip::enter_(ksys::act::ai::InlineParamPack* params) {
    ASPlayRotateTurnToTarget::enter_(params);
}

void BackFlip::leave_() {
    ASPlayRotateTurnToTarget::leave_();
}

void BackFlip::loadParams_() {
    ASPlayRotateTurnToTarget::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mPosRestRatio_s, "PosRestRatio");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mNearGrHeight_s, "NearGrHeight");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void BackFlip::calc_() {
    ASPlayRotateTurnToTarget::calc_();
}

}  // namespace uking::action

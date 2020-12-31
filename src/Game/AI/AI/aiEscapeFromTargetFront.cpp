#include "Game/AI/AI/aiEscapeFromTargetFront.h"

namespace uking::ai {

EscapeFromTargetFront::EscapeFromTargetFront(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EscapeFromTargetFront::~EscapeFromTargetFront() = default;

bool EscapeFromTargetFront::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EscapeFromTargetFront::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EscapeFromTargetFront::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EscapeFromTargetFront::loadParams_() {
    getStaticParam(&mMaxTime_s, "MaxTime");
    getStaticParam(&mMinTime_s, "MinTime");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mUseCameraFrontByTargetPlayer_s, "UseCameraFrontByTargetPlayer");
}

}  // namespace uking::ai

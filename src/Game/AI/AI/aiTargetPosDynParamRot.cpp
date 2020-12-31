#include "Game/AI/AI/aiTargetPosDynParamRot.h"

namespace uking::ai {

TargetPosDynParamRot::TargetPosDynParamRot(const InitArg& arg) : TargetPosAI(arg) {}

TargetPosDynParamRot::~TargetPosDynParamRot() = default;

bool TargetPosDynParamRot::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPosDynParamRot::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPosDynParamRot::leave_() {
    TargetPosAI::leave_();
}

void TargetPosDynParamRot::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mMinDist_s, "MinDist");
    getDynamicParam(&mAngle_d, "Angle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

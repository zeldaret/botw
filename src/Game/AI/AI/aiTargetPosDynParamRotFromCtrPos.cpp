#include "Game/AI/AI/aiTargetPosDynParamRotFromCtrPos.h"

namespace uking::ai {

TargetPosDynParamRotFromCtrPos::TargetPosDynParamRotFromCtrPos(const InitArg& arg)
    : TargetPosDynParamRot(arg) {}

TargetPosDynParamRotFromCtrPos::~TargetPosDynParamRotFromCtrPos() = default;

bool TargetPosDynParamRotFromCtrPos::init_(sead::Heap* heap) {
    return TargetPosDynParamRot::init_(heap);
}

void TargetPosDynParamRotFromCtrPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosDynParamRot::enter_(params);
}

void TargetPosDynParamRotFromCtrPos::leave_() {
    TargetPosDynParamRot::leave_();
}

void TargetPosDynParamRotFromCtrPos::loadParams_() {
    TargetPosDynParamRot::loadParams_();
    getDynamicParam(&mCenterPos_d, "CenterPos");
}

}  // namespace uking::ai

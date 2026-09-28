#include "Game/Actor/AI/aiTargetPosDynParamRotFromCtrPos.h"

namespace uking::ai {

TargetPosDynParamRotFromCtrPos::TargetPosDynParamRotFromCtrPos(const InitArg& arg)
    : TargetPosDynParamRotFromMyPos(arg) {}

TargetPosDynParamRotFromCtrPos::~TargetPosDynParamRotFromCtrPos() = default;

bool TargetPosDynParamRotFromCtrPos::init_(sead::Heap* heap) {
    return TargetPosDynParamRotFromMyPos::init_(heap);
}

void TargetPosDynParamRotFromCtrPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosDynParamRotFromMyPos::enter_(params);
}

void TargetPosDynParamRotFromCtrPos::leave_() {
    TargetPosDynParamRotFromMyPos::leave_();
}

void TargetPosDynParamRotFromCtrPos::loadParams_() {
    TargetPosDynParamRotFromMyPos::loadParams_();
    getDynamicParam(&mCenterPos_d, "CenterPos");
}

}  // namespace uking::ai

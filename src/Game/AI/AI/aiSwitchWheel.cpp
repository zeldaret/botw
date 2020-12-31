#include "Game/AI/AI/aiSwitchWheel.h"

namespace uking::ai {

SwitchWheel::SwitchWheel(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchWheel::~SwitchWheel() = default;

bool SwitchWheel::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchWheel::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwitchWheel::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchWheel::loadParams_() {
    getStaticParam(&mRotateStartRad_s, "RotateStartRad");
    getStaticParam(&mRotateEndRad_s, "RotateEndRad");
    getStaticParam(&mReverseEndRad_s, "ReverseEndRad");
    getStaticParam(&mReverseStartRad_s, "ReverseStartRad");
    getStaticParam(&mIsAbleToReverse_s, "IsAbleToReverse");
    getMapUnitParam(&mRotAxis_m, "RotAxis");
}

}  // namespace uking::ai

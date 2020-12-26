#include "Game/AI/Action/actionMotorcycleAppear.h"

namespace uking::action {

MotorcycleAppear::MotorcycleAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MotorcycleAppear::~MotorcycleAppear() = default;

bool MotorcycleAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MotorcycleAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MotorcycleAppear::leave_() {
    ksys::act::ai::Action::leave_();
}

void MotorcycleAppear::loadParams_() {
    getStaticParam(&mHideFrames_s, "HideFrames");
    getStaticParam(&mModelWarpEffectFrames_s, "ModelWarpEffectFrames");
    getStaticParam(&mEndFrames_s, "EndFrames");
}

void MotorcycleAppear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

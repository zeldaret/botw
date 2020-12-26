#include "Game/AI/Action/actionMotorcycleDisappear.h"

namespace uking::action {

MotorcycleDisappear::MotorcycleDisappear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MotorcycleDisappear::~MotorcycleDisappear() = default;

bool MotorcycleDisappear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MotorcycleDisappear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MotorcycleDisappear::leave_() {
    ksys::act::ai::Action::leave_();
}

void MotorcycleDisappear::loadParams_() {
    getStaticParam(&mModelWarpEffectFrames_s, "ModelWarpEffectFrames");
    getDynamicParam(&mDisappearEffectName_d, "DisappearEffectName");
}

void MotorcycleDisappear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

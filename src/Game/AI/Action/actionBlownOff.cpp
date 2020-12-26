#include "Game/AI/Action/actionBlownOff.h"

namespace uking::action {

BlownOff::BlownOff(const InitArg& arg) : Ragdoll(arg) {}

BlownOff::~BlownOff() = default;

bool BlownOff::init_(sead::Heap* heap) {
    return Ragdoll::init_(heap);
}

void BlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    Ragdoll::enter_(params);
}

void BlownOff::leave_() {
    Ragdoll::leave_();
}

void BlownOff::loadParams_() {
    getStaticParam(&mAddTime_s, "AddTime");
    getStaticParam(&mLifeReflexRatio_s, "LifeReflexRatio");
    getStaticParam(&mImpulseRatio_s, "ImpulseRatio");
    Ragdoll::loadParams_();
}

void BlownOff::calc_() {
    Ragdoll::calc_();
}

}  // namespace uking::action

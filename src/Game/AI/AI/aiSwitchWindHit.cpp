#include "Game/AI/AI/aiSwitchWindHit.h"

namespace uking::ai {

SwitchWindHit::SwitchWindHit(const InitArg& arg) : SwitchAI(arg) {}

SwitchWindHit::~SwitchWindHit() = default;

bool SwitchWindHit::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchWindHit::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
}

void SwitchWindHit::leave_() {
    SwitchAI::leave_();
}

void SwitchWindHit::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mWaitTime_s, "WaitTime");
}

}  // namespace uking::ai

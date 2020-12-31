#include "Game/AI/AI/aiSwitchHit.h"

namespace uking::ai {

SwitchHit::SwitchHit(const InitArg& arg) : SwitchAI(arg) {}

SwitchHit::~SwitchHit() = default;

bool SwitchHit::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchHit::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
}

void SwitchHit::leave_() {
    SwitchAI::leave_();
}

void SwitchHit::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mWaitTime_s, "WaitTime");
}

}  // namespace uking::ai

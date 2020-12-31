#include "Game/AI/AI/aiSwitchHitOnce.h"

namespace uking::ai {

SwitchHitOnce::SwitchHitOnce(const InitArg& arg) : SwitchHit(arg) {}

bool SwitchHitOnce::init_(sead::Heap* heap) {
    return SwitchHit::init_(heap);
}

void SwitchHitOnce::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchHit::enter_(params);
}

void SwitchHitOnce::leave_() {
    SwitchHit::leave_();
}

}  // namespace uking::ai

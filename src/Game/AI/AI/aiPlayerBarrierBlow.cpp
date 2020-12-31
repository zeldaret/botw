#include "Game/AI/AI/aiPlayerBarrierBlow.h"

namespace uking::ai {

PlayerBarrierBlow::PlayerBarrierBlow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerBarrierBlow::~PlayerBarrierBlow() = default;

bool PlayerBarrierBlow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerBarrierBlow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerBarrierBlow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerBarrierBlow::loadParams_() {
    getStaticParam(&mBlowRagdollTime_s, "BlowRagdollTime");
}

}  // namespace uking::ai

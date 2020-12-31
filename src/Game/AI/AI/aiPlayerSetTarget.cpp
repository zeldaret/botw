#include "Game/AI/AI/aiPlayerSetTarget.h"

namespace uking::ai {

PlayerSetTarget::PlayerSetTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerSetTarget::~PlayerSetTarget() = default;

bool PlayerSetTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerSetTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerSetTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerSetTarget::loadParams_() {}

}  // namespace uking::ai

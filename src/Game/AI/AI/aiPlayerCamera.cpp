#include "Game/AI/AI/aiPlayerCamera.h"

namespace uking::ai {

PlayerCamera::PlayerCamera(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerCamera::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerCamera::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai

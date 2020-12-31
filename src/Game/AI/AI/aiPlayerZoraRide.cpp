#include "Game/AI/AI/aiPlayerZoraRide.h"

namespace uking::ai {

PlayerZoraRide::PlayerZoraRide(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerZoraRide::~PlayerZoraRide() = default;

bool PlayerZoraRide::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerZoraRide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerZoraRide::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerZoraRide::loadParams_() {}

}  // namespace uking::ai

#include "Game/AI/AI/aiPlayerClimb.h"

namespace uking::ai {

PlayerClimb::PlayerClimb(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerClimb::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerClimb::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerClimb::loadParams_() {
    getStaticParam(&mNoClimbTime_s, "NoClimbTime");
}

}  // namespace uking::ai

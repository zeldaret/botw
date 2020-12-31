#include "Game/AI/AI/aiPlayerCaught.h"

namespace uking::ai {

PlayerCaught::PlayerCaught(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerCaught::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerCaught::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerCaught::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai

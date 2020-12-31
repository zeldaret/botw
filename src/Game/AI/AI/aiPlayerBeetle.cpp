#include "Game/AI/AI/aiPlayerBeetle.h"

namespace uking::ai {

PlayerBeetle::PlayerBeetle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerBeetle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerBeetle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerBeetle::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai

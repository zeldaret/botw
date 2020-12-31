#include "Game/AI/AI/aiPlayerSit.h"

namespace uking::ai {

PlayerSit::PlayerSit(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerSit::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerSit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerSit::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai

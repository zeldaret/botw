#include "Game/AI/AI/aiPlayerAttack.h"

namespace uking::ai {

PlayerAttack::PlayerAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerAttack::loadParams_() {}

}  // namespace uking::ai

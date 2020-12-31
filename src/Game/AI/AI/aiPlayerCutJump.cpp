#include "Game/AI/AI/aiPlayerCutJump.h"

namespace uking::ai {

PlayerCutJump::PlayerCutJump(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerCutJump::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerCutJump::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerCutJump::loadParams_() {}

}  // namespace uking::ai

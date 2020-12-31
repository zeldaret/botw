#include "Game/AI/AI/aiPlayerDead.h"

namespace uking::ai {

PlayerDead::PlayerDead(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerDead::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerDead::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerDead::loadParams_() {
    getStaticParam(&mRumbleType_s, "RumbleType");
    getStaticParam(&mRumblePower_s, "RumblePower");
}

}  // namespace uking::ai

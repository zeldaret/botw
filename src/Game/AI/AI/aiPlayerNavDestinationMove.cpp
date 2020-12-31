#include "Game/AI/AI/aiPlayerNavDestinationMove.h"

namespace uking::ai {

PlayerNavDestinationMove::PlayerNavDestinationMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerNavDestinationMove::~PlayerNavDestinationMove() = default;

bool PlayerNavDestinationMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerNavDestinationMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerNavDestinationMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerNavDestinationMove::loadParams_() {
    getDynamicParam(&mDestPosX_d, "DestPosX");
    getDynamicParam(&mDestPosY_d, "DestPosY");
    getDynamicParam(&mDestPosZ_d, "DestPosZ");
    getDynamicParam(&mStickValue_d, "StickValue");
}

}  // namespace uking::ai

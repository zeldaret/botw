#include "Game/AI/AI/aiPlayerWaterFall.h"

namespace uking::ai {

PlayerWaterFall::PlayerWaterFall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerWaterFall::~PlayerWaterFall() = default;

bool PlayerWaterFall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerWaterFall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerWaterFall::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerWaterFall::loadParams_() {}

}  // namespace uking::ai

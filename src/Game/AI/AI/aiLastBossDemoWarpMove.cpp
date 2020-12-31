#include "Game/AI/AI/aiLastBossDemoWarpMove.h"

namespace uking::ai {

LastBossDemoWarpMove::LastBossDemoWarpMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossDemoWarpMove::~LastBossDemoWarpMove() = default;

bool LastBossDemoWarpMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossDemoWarpMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossDemoWarpMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossDemoWarpMove::loadParams_() {}

}  // namespace uking::ai

#include "Game/AI/AI/aiRemainsFireBattleMove.h"

namespace uking::ai {

RemainsFireBattleMove::RemainsFireBattleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsFireBattleMove::~RemainsFireBattleMove() = default;

bool RemainsFireBattleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsFireBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsFireBattleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsFireBattleMove::loadParams_() {}

}  // namespace uking::ai

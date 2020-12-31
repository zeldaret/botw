#include "Game/AI/AI/aiRemainsFireBattleStepSelector.h"

namespace uking::ai {

RemainsFireBattleStepSelector::RemainsFireBattleStepSelector(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RemainsFireBattleStepSelector::~RemainsFireBattleStepSelector() = default;

bool RemainsFireBattleStepSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsFireBattleStepSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsFireBattleStepSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsFireBattleStepSelector::loadParams_() {}

}  // namespace uking::ai

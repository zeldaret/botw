#include "Game/AI/AI/aiWillBallAttackLevelSelect.h"

namespace uking::ai {

WillBallAttackLevelSelect::WillBallAttackLevelSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallAttackLevelSelect::~WillBallAttackLevelSelect() = default;

bool WillBallAttackLevelSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallAttackLevelSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WillBallAttackLevelSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WillBallAttackLevelSelect::loadParams_() {
    getDynamicParam(&mLevel_d, "Level");
}

}  // namespace uking::ai

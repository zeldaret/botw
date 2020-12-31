#include "Game/AI/AI/aiGuardianMiniBattleStateSelect.h"

namespace uking::ai {

GuardianMiniBattleStateSelect::GuardianMiniBattleStateSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniBattleStateSelect::~GuardianMiniBattleStateSelect() = default;

void GuardianMiniBattleStateSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMiniBattleStateSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniBattleStateSelect::loadParams_() {
    getStaticParam(&mSecondLifeRatio_s, "SecondLifeRatio");
    getStaticParam(&mFinalLifeRatio_s, "FinalLifeRatio");
    getStaticParam(&mIsEnterOnly_s, "IsEnterOnly");
}

}  // namespace uking::ai

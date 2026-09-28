#include "Game/Actor/AI/aiAssassinMiddleMagicAfter.h"

namespace uking::ai {

AssassinMiddleMagicAfter::AssassinMiddleMagicAfter(const InitArg& arg)
    : TargetHeightAreaSelect(arg) {}

AssassinMiddleMagicAfter::~AssassinMiddleMagicAfter() = default;

bool AssassinMiddleMagicAfter::init_(sead::Heap* heap) {
    return TargetHeightAreaSelect::init_(heap);
}

void AssassinMiddleMagicAfter::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetHeightAreaSelect::enter_(params);
}

void AssassinMiddleMagicAfter::leave_() {
    TargetHeightAreaSelect::leave_();
}

void AssassinMiddleMagicAfter::loadParams_() {
    TargetHeightAreaSelect::loadParams_();
    getAITreeVariable(&mIsInterseptAttack_a, "IsInterseptAttack");
}

}  // namespace uking::ai

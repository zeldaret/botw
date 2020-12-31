#include "Game/AI/AI/aiAssassinMiddleMagicAfter.h"

namespace uking::ai {

AssassinMiddleMagicAfter::AssassinMiddleMagicAfter(const InitArg& arg)
    : AssassinMagicTgtSelect(arg) {}

AssassinMiddleMagicAfter::~AssassinMiddleMagicAfter() = default;

bool AssassinMiddleMagicAfter::init_(sead::Heap* heap) {
    return AssassinMagicTgtSelect::init_(heap);
}

void AssassinMiddleMagicAfter::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinMagicTgtSelect::enter_(params);
}

void AssassinMiddleMagicAfter::leave_() {
    AssassinMagicTgtSelect::leave_();
}

void AssassinMiddleMagicAfter::loadParams_() {
    AssassinMagicTgtSelect::loadParams_();
    getAITreeVariable(&mIsInterseptAttack_a, "IsInterseptAttack");
}

}  // namespace uking::ai

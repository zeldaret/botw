#include "Game/AI/AI/aiForestGiantClosestAttackSelect.h"

namespace uking::ai {

ForestGiantClosestAttackSelect::ForestGiantClosestAttackSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

ForestGiantClosestAttackSelect::~ForestGiantClosestAttackSelect() = default;

bool ForestGiantClosestAttackSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForestGiantClosestAttackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ForestGiantClosestAttackSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ForestGiantClosestAttackSelect::loadParams_() {
    getStaticParam(&mHipDropRate_s, "HipDropRate");
    getStaticParam(&mHipDropRateFar_s, "HipDropRateFar");
    getStaticParam(&mFarDist_s, "FarDist");
}

}  // namespace uking::ai

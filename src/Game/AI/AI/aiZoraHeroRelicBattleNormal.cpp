#include "Game/AI/AI/aiZoraHeroRelicBattleNormal.h"

namespace uking::ai {

ZoraHeroRelicBattleNormal::ZoraHeroRelicBattleNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZoraHeroRelicBattleNormal::~ZoraHeroRelicBattleNormal() = default;

bool ZoraHeroRelicBattleNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ZoraHeroRelicBattleNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ZoraHeroRelicBattleNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ZoraHeroRelicBattleNormal::loadParams_() {
    getStaticParam(&mWarpDistanceXZ_s, "WarpDistanceXZ");
    getStaticParam(&mNearPlayerDistanceXZ_s, "NearPlayerDistanceXZ");
}

}  // namespace uking::ai

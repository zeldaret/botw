#include "Game/AI/AI/aiAssassinBossFirstBattleMove.h"

namespace uking::ai {

AssassinBossFirstBattleMove::AssassinBossFirstBattleMove(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinBossFirstBattleMove::~AssassinBossFirstBattleMove() = default;

bool AssassinBossFirstBattleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinBossFirstBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AssassinBossFirstBattleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBossFirstBattleMove::loadParams_() {
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mCheckTargetDist_s, "CheckTargetDist");
    getStaticParam(&mTooFarXZ_s, "TooFarXZ");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

}  // namespace uking::ai

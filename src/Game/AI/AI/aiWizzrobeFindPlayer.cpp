#include "Game/AI/AI/aiWizzrobeFindPlayer.h"

namespace uking::ai {

WizzrobeFindPlayer::WizzrobeFindPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeFindPlayer::~WizzrobeFindPlayer() = default;

bool WizzrobeFindPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeFindPlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeFindPlayer::loadParams_() {
    getStaticParam(&mHomeTerritoryWidth_s, "HomeTerritoryWidth");
    getStaticParam(&mHomeTerritoryHeight_s, "HomeTerritoryHeight");
    getStaticParam(&mBattleTerritoryWidth_s, "BattleTerritoryWidth");
    getAITreeVariable(&mIsWizzrobeInBattleAreaFlag_a, "IsWizzrobeInBattleAreaFlag");
}

}  // namespace uking::ai

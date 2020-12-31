#include "Game/AI/AI/aiZoraHeroRelicBattleRidePlayer.h"

namespace uking::ai {

ZoraHeroRelicBattleRidePlayer::ZoraHeroRelicBattleRidePlayer(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

ZoraHeroRelicBattleRidePlayer::~ZoraHeroRelicBattleRidePlayer() = default;

bool ZoraHeroRelicBattleRidePlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ZoraHeroRelicBattleRidePlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ZoraHeroRelicBattleRidePlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ZoraHeroRelicBattleRidePlayer::loadParams_() {
    getAITreeVariable(&mZoraHeroShowMsgUnit_a, "ZoraHeroShowMsgUnit");
}

}  // namespace uking::ai

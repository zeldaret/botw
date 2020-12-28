#include "Game/AI/Action/actionZoraHeroRescuePlayer.h"

namespace uking::action {

ZoraHeroRescuePlayer::ZoraHeroRescuePlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ZoraHeroRescuePlayer::~ZoraHeroRescuePlayer() = default;

bool ZoraHeroRescuePlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ZoraHeroRescuePlayer::loadParams_() {
    getAITreeVariable(&mZoraHeroShowMsgUnit_a, "ZoraHeroShowMsgUnit");
}

}  // namespace uking::action

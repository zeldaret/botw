#include "Game/AI/Action/actionNPCStartTurnToPlayer.h"

namespace uking::action {

NPCStartTurnToPlayer::NPCStartTurnToPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCStartTurnToPlayer::~NPCStartTurnToPlayer() = default;

bool NPCStartTurnToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCStartTurnToPlayer::loadParams_() {
    getDynamicParam(&mTurnRange_d, "TurnRange");
}

}  // namespace uking::action

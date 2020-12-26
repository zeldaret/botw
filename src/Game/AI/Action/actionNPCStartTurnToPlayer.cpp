#include "Game/AI/Action/actionNPCStartTurnToPlayer.h"

namespace uking::action {

NPCStartTurnToPlayer::NPCStartTurnToPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCStartTurnToPlayer::~NPCStartTurnToPlayer() = default;

bool NPCStartTurnToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCStartTurnToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCStartTurnToPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCStartTurnToPlayer::loadParams_() {
    getDynamicParam(&mTurnRange_d, "TurnRange");
}

void NPCStartTurnToPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

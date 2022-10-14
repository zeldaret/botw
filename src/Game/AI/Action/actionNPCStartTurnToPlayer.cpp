#include "Game/AI/Action/actionNPCStartTurnToPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

NPCStartTurnToPlayer::NPCStartTurnToPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCStartTurnToPlayer::~NPCStartTurnToPlayer() = default;

bool NPCStartTurnToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool NPCStartTurnToPlayer::oneShot_() {
    mValue = *mTurnRange_d * 0.5f;

    sendMessage(*mActor->getMesTransceiverId(), ksys::MessageType(0x8000078), &mValue);

    return ksys::act::ai::Action::oneShot_();
}

void NPCStartTurnToPlayer::loadParams_() {
    getDynamicParam(&mTurnRange_d, "TurnRange");
}

}  // namespace uking::action

#include "Game/AI/Action/actionEventMiniGameTimerWrite.h"

namespace uking::action {

EventMiniGameTimerWrite::EventMiniGameTimerWrite(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameTimerWrite::~EventMiniGameTimerWrite() = default;

bool EventMiniGameTimerWrite::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameTimerWrite::loadParams_() {
    getDynamicParam(&mGameDataIntNameMintues_d, "GameDataIntNameMintues");
    getDynamicParam(&mGameDataIntNameSeconds_d, "GameDataIntNameSeconds");
    getDynamicParam(&mGameDataIntNameMiliseconds_d, "GameDataIntNameMiliseconds");
}

}  // namespace uking::action

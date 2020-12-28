#include "Game/AI/Action/actionEventUpdateMiniGameBestScore.h"

namespace uking::action {

EventUpdateMiniGameBestScore::EventUpdateMiniGameBestScore(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventUpdateMiniGameBestScore::~EventUpdateMiniGameBestScore() = default;

bool EventUpdateMiniGameBestScore::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventUpdateMiniGameBestScore::loadParams_() {
    getDynamicParam(&mType_d, "Type");
}

}  // namespace uking::action

#include "Game/AI/Action/actionEventUpdateMiniGameBestScore.h"

namespace uking::action {

EventUpdateMiniGameBestScore::EventUpdateMiniGameBestScore(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventUpdateMiniGameBestScore::~EventUpdateMiniGameBestScore() = default;

bool EventUpdateMiniGameBestScore::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventUpdateMiniGameBestScore::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventUpdateMiniGameBestScore::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventUpdateMiniGameBestScore::loadParams_() {
    getDynamicParam(&mType_d, "Type");
}

void EventUpdateMiniGameBestScore::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

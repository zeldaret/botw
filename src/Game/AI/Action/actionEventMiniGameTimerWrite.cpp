#include "Game/AI/Action/actionEventMiniGameTimerWrite.h"

namespace uking::action {

EventMiniGameTimerWrite::EventMiniGameTimerWrite(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventMiniGameTimerWrite::~EventMiniGameTimerWrite() = default;

bool EventMiniGameTimerWrite::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventMiniGameTimerWrite::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventMiniGameTimerWrite::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventMiniGameTimerWrite::loadParams_() {
    getDynamicParam(&mGameDataIntNameMintues_d, "GameDataIntNameMintues");
    getDynamicParam(&mGameDataIntNameSeconds_d, "GameDataIntNameSeconds");
    getDynamicParam(&mGameDataIntNameMiliseconds_d, "GameDataIntNameMiliseconds");
}

void EventMiniGameTimerWrite::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

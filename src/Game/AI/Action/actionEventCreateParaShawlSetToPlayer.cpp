#include "Game/AI/Action/actionEventCreateParaShawlSetToPlayer.h"

namespace uking::action {

EventCreateParaShawlSetToPlayer::EventCreateParaShawlSetToPlayer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventCreateParaShawlSetToPlayer::~EventCreateParaShawlSetToPlayer() = default;

bool EventCreateParaShawlSetToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCreateParaShawlSetToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventCreateParaShawlSetToPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventCreateParaShawlSetToPlayer::loadParams_() {
    getDynamicParam(&mParaShawlType_d, "ParaShawlType");
}

void EventCreateParaShawlSetToPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

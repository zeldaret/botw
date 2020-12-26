#include "Game/AI/Action/actionEventPlayMovieAction.h"

namespace uking::action {

EventPlayMovieAction::EventPlayMovieAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayMovieAction::~EventPlayMovieAction() = default;

bool EventPlayMovieAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayMovieAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayMovieAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayMovieAction::loadParams_() {
    getDynamicParam(&mFileName_d, "FileName");
}

void EventPlayMovieAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

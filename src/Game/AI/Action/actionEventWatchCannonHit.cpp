#include "Game/AI/Action/actionEventWatchCannonHit.h"

namespace uking::action {

EventWatchCannonHit::EventWatchCannonHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventWatchCannonHit::~EventWatchCannonHit() = default;

bool EventWatchCannonHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventWatchCannonHit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventWatchCannonHit::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventWatchCannonHit::loadParams_() {
    getDynamicParam(&mWatchFrame_d, "WatchFrame");
    getDynamicParam(&mXLinkKey_d, "XLinkKey");
}

void EventWatchCannonHit::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

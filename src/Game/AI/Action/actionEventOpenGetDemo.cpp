#include "Game/AI/Action/actionEventOpenGetDemo.h"

namespace uking::action {

EventOpenGetDemo::EventOpenGetDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventOpenGetDemo::~EventOpenGetDemo() = default;

bool EventOpenGetDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventOpenGetDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventOpenGetDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventOpenGetDemo::loadParams_() {
    getDynamicParam(&mIsInvalidOpenPouch_d, "IsInvalidOpenPouch");
}

void EventOpenGetDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

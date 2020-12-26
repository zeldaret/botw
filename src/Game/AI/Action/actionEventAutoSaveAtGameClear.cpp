#include "Game/AI/Action/actionEventAutoSaveAtGameClear.h"

namespace uking::action {

EventAutoSaveAtGameClear::EventAutoSaveAtGameClear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventAutoSaveAtGameClear::~EventAutoSaveAtGameClear() = default;

bool EventAutoSaveAtGameClear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAutoSaveAtGameClear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventAutoSaveAtGameClear::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAutoSaveAtGameClear::loadParams_() {
    getDynamicParam(&mRestartYDegree_d, "RestartYDegree");
    getDynamicParam(&mGameClearFlag_d, "GameClearFlag");
    getDynamicParam(&mRestartPoint_d, "RestartPoint");
}

void EventAutoSaveAtGameClear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

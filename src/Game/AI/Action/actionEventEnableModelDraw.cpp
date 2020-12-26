#include "Game/AI/Action/actionEventEnableModelDraw.h"

namespace uking::action {

EventEnableModelDraw::EventEnableModelDraw(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventEnableModelDraw::~EventEnableModelDraw() = default;

bool EventEnableModelDraw::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventEnableModelDraw::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventEnableModelDraw::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventEnableModelDraw::loadParams_() {}

void EventEnableModelDraw::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

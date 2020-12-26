#include "Game/AI/Action/actionStopEventMiniGameTime.h"

namespace uking::action {

StopEventMiniGameTime::StopEventMiniGameTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StopEventMiniGameTime::~StopEventMiniGameTime() = default;

bool StopEventMiniGameTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StopEventMiniGameTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StopEventMiniGameTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void StopEventMiniGameTime::loadParams_() {}

void StopEventMiniGameTime::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

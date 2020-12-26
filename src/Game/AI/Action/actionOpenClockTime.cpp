#include "Game/AI/Action/actionOpenClockTime.h"

namespace uking::action {

OpenClockTime::OpenClockTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenClockTime::~OpenClockTime() = default;

bool OpenClockTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenClockTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenClockTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenClockTime::loadParams_() {}

void OpenClockTime::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionCloseClockTime.h"

namespace uking::action {

CloseClockTime::CloseClockTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CloseClockTime::~CloseClockTime() = default;

bool CloseClockTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CloseClockTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CloseClockTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void CloseClockTime::loadParams_() {}

void CloseClockTime::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/Actor/Action/actionWaitBase.h"

namespace uking::action {

WaitBase::WaitBase(const InitArg& arg) : StopBase(arg) {}

WaitBase::~WaitBase() = default;

void WaitBase::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void WaitBase::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void WaitBase::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action

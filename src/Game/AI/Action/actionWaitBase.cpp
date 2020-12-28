#include "Game/AI/Action/actionWaitBase.h"

namespace uking::action {

WaitBase::WaitBase(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

WaitBase::~WaitBase() = default;

void WaitBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void WaitBase::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void WaitBase::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action

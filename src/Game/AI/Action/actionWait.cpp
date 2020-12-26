#include "Game/AI/Action/actionWait.h"

namespace uking::action {

Wait::Wait(const InitArg& arg) : WaitBase(arg) {}

Wait::~Wait() = default;

bool Wait::init_(sead::Heap* heap) {
    return WaitBase::init_(heap);
}

void Wait::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitBase::enter_(params);
}

void Wait::leave_() {
    WaitBase::leave_();
}

void Wait::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void Wait::calc_() {
    WaitBase::calc_();
}

}  // namespace uking::action

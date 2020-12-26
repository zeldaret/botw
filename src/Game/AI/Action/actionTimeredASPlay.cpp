#include "Game/AI/Action/actionTimeredASPlay.h"

namespace uking::action {

TimeredASPlay::TimeredASPlay(const InitArg& arg) : WaitBase(arg) {}

TimeredASPlay::~TimeredASPlay() = default;

bool TimeredASPlay::init_(sead::Heap* heap) {
    return WaitBase::init_(heap);
}

void TimeredASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitBase::enter_(params);
}

void TimeredASPlay::leave_() {
    WaitBase::leave_();
}

void TimeredASPlay::loadParams_() {
    WaitBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void TimeredASPlay::calc_() {
    WaitBase::calc_();
}

}  // namespace uking::action

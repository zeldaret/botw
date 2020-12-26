#include "Game/AI/Action/actionKeepPosInWater.h"

namespace uking::action {

KeepPosInWater::KeepPosInWater(const InitArg& arg) : WaitBase(arg) {}

KeepPosInWater::~KeepPosInWater() = default;

bool KeepPosInWater::init_(sead::Heap* heap) {
    return WaitBase::init_(heap);
}

void KeepPosInWater::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitBase::enter_(params);
}

void KeepPosInWater::leave_() {
    WaitBase::leave_();
}

void KeepPosInWater::loadParams_() {
    WaitBase::loadParams_();
    getStaticParam(&mForceTurnLimitSpeedStream_s, "ForceTurnLimitSpeedStream");
    getStaticParam(&mChaceFrontRate_s, "ChaceFrontRate");
    getStaticParam(&mChaceAngSpeedMax_s, "ChaceAngSpeedMax");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void KeepPosInWater::calc_() {
    WaitBase::calc_();
}

}  // namespace uking::action

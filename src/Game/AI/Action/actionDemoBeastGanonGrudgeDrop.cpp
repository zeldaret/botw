#include "Game/AI/Action/actionDemoBeastGanonGrudgeDrop.h"

namespace uking::action {

DemoBeastGanonGrudgeDrop::DemoBeastGanonGrudgeDrop(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoBeastGanonGrudgeDrop::~DemoBeastGanonGrudgeDrop() = default;

bool DemoBeastGanonGrudgeDrop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoBeastGanonGrudgeDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoBeastGanonGrudgeDrop::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoBeastGanonGrudgeDrop::loadParams_() {
    getStaticParam(&mGrudeRainObject_s, "GrudeRainObject");
    getDynamicParam(&mTimer_d, "Timer");
    getDynamicParam(&mASName_d, "ASName");
    getDynamicParam(&mFallPoint1_d, "FallPoint1");
}

void DemoBeastGanonGrudgeDrop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionStrangeBeacon.h"

namespace uking::action {

StrangeBeacon::StrangeBeacon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StrangeBeacon::~StrangeBeacon() = default;

bool StrangeBeacon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StrangeBeacon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StrangeBeacon::leave_() {
    ksys::act::ai::Action::leave_();
}

void StrangeBeacon::loadParams_() {
    getStaticParam(&mSaveFlag_s, "SaveFlag");
    getStaticParam(&mCalcStartFlag_s, "CalcStartFlag");
    getStaticParam(&mKeyName_s, "KeyName");
}

void StrangeBeacon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

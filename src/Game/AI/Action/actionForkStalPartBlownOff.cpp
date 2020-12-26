#include "Game/AI/Action/actionForkStalPartBlownOff.h"

namespace uking::action {

ForkStalPartBlownOff::ForkStalPartBlownOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkStalPartBlownOff::~ForkStalPartBlownOff() = default;

bool ForkStalPartBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStalPartBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkStalPartBlownOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkStalPartBlownOff::loadParams_() {
    getStaticParam(&mShootParts_s, "ShootParts");
    getStaticParam(&mShootSpeed_s, "ShootSpeed");
    getStaticParam(&mLifeRate_s, "LifeRate");
    getStaticParam(&mBaseNodeName_s, "BaseNodeName");
    getStaticParam(&mShootDir_s, "ShootDir");
}

void ForkStalPartBlownOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionGearStop.h"

namespace uking::action {

GearStop::GearStop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GearStop::~GearStop() = default;

bool GearStop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GearStop::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GearStop::leave_() {
    ksys::act::ai::Action::leave_();
}

void GearStop::loadParams_() {
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
    getMapUnitParam(&mRotateDamp_m, "RotateDamp");
}

void GearStop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

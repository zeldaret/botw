#include "Game/AI/Action/actionDgnObjDLCSpurGearB01.h"

namespace uking::action {

DgnObjDLCSpurGearB01::DgnObjDLCSpurGearB01(const InitArg& arg) : GearRotate(arg) {}

DgnObjDLCSpurGearB01::~DgnObjDLCSpurGearB01() = default;

bool DgnObjDLCSpurGearB01::init_(sead::Heap* heap) {
    return GearRotate::init_(heap);
}

void DgnObjDLCSpurGearB01::enter_(ksys::act::ai::InlineParamPack* params) {
    GearRotate::enter_(params);
}

void DgnObjDLCSpurGearB01::leave_() {
    GearRotate::leave_();
}

void DgnObjDLCSpurGearB01::loadParams_() {
    GearRotate::loadParams_();
}

void DgnObjDLCSpurGearB01::calc_() {
    GearRotate::calc_();
}

}  // namespace uking::action

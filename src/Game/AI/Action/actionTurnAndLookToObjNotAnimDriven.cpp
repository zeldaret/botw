#include "Game/AI/Action/actionTurnAndLookToObjNotAnimDriven.h"

namespace uking::action {

TurnAndLookToObjNotAnimDriven::TurnAndLookToObjNotAnimDriven(const InitArg& arg)
    : LookAtObjectBase(arg) {}

TurnAndLookToObjNotAnimDriven::~TurnAndLookToObjNotAnimDriven() = default;

bool TurnAndLookToObjNotAnimDriven::init_(sead::Heap* heap) {
    return LookAtObjectBase::init_(heap);
}

void TurnAndLookToObjNotAnimDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    LookAtObjectBase::enter_(params);
}

void TurnAndLookToObjNotAnimDriven::leave_() {
    LookAtObjectBase::leave_();
}

void TurnAndLookToObjNotAnimDriven::loadParams_() {
    LookAtObjectBase::loadParams_();
    getDynamicParam(&mRotSpdMax_d, "RotSpdMax");
    getDynamicParam(&mRotSpdMin_d, "RotSpdMin");
    getDynamicParam(&mRotInitSpd_d, "RotInitSpd");
    getDynamicParam(&mRotAccel_d, "RotAccel");
    getDynamicParam(&mRotRate_d, "RotRate");
}

void TurnAndLookToObjNotAnimDriven::calc_() {
    LookAtObjectBase::calc_();
}

}  // namespace uking::action

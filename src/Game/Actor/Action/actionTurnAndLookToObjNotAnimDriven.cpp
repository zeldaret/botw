#include "Game/Actor/Action/actionTurnAndLookToObjNotAnimDriven.h"

namespace uking::action {

TurnAndLookToObjNotAnimDriven::TurnAndLookToObjNotAnimDriven(const InitArg& arg)
    : TurnAndLookToObjBase(arg) {}

TurnAndLookToObjNotAnimDriven::~TurnAndLookToObjNotAnimDriven() = default;

bool TurnAndLookToObjNotAnimDriven::init_(sead::Heap* heap) {
    return TurnAndLookToObjBase::init_(heap);
}

void TurnAndLookToObjNotAnimDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnAndLookToObjBase::enter_(params);
}

void TurnAndLookToObjNotAnimDriven::leave_() {
    TurnAndLookToObjBase::leave_();
}

void TurnAndLookToObjNotAnimDriven::loadParams_() {
    TurnAndLookToObjBase::loadParams_();
    getDynamicParam(&mRotSpdMax_d, "RotSpdMax");
    getDynamicParam(&mRotSpdMin_d, "RotSpdMin");
    getDynamicParam(&mRotInitSpd_d, "RotInitSpd");
    getDynamicParam(&mRotAccel_d, "RotAccel");
    getDynamicParam(&mRotRate_d, "RotRate");
}

void TurnAndLookToObjNotAnimDriven::calc_() {
    TurnAndLookToObjBase::calc_();
}

}  // namespace uking::action

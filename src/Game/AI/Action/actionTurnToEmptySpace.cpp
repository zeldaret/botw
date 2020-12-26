#include "Game/AI/Action/actionTurnToEmptySpace.h"

namespace uking::action {

TurnToEmptySpace::TurnToEmptySpace(const InitArg& arg) : TurnAndLookToObjNotAnimDriven(arg) {}

TurnToEmptySpace::~TurnToEmptySpace() = default;

bool TurnToEmptySpace::init_(sead::Heap* heap) {
    return TurnAndLookToObjNotAnimDriven::init_(heap);
}

void TurnToEmptySpace::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnAndLookToObjNotAnimDriven::enter_(params);
}

void TurnToEmptySpace::leave_() {
    TurnAndLookToObjNotAnimDriven::leave_();
}

void TurnToEmptySpace::loadParams_() {
    TurnAndLookToObjNotAnimDriven::loadParams_();
    getStaticParam(&mCheckDistance_s, "CheckDistance");
    getStaticParam(&mCheckAngOffset_s, "CheckAngOffset");
    getStaticParam(&mCheckShapeRadius_s, "CheckShapeRadius");
    getStaticParam(&mCastOffset_s, "CastOffset");
    getStaticParam(&mCheckAngOffsetX_s, "CheckAngOffsetX");
}

void TurnToEmptySpace::calc_() {
    TurnAndLookToObjNotAnimDriven::calc_();
}

}  // namespace uking::action

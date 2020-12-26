#include "Game/AI/Action/actionSetComebackPosition.h"

namespace uking::action {

SetComebackPosition::SetComebackPosition(const InitArg& arg) : AreaTagAction(arg) {}

SetComebackPosition::~SetComebackPosition() = default;

bool SetComebackPosition::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void SetComebackPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SetComebackPosition::leave_() {
    AreaTagAction::leave_();
}

void SetComebackPosition::loadParams_() {
    getMapUnitParam(&mAngleY_m, "AngleY");
}

void SetComebackPosition::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action

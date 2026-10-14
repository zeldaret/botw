#include "Game/Actor/Action/actionSetComebackPosition.h"

namespace uking::action {

SetComebackPosition::SetComebackPosition(const InitArg& arg) : AreaActionBase(arg) {}

SetComebackPosition::~SetComebackPosition() = default;

bool SetComebackPosition::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void SetComebackPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void SetComebackPosition::leave_() {
    AreaActionBase::leave_();
}

void SetComebackPosition::loadParams_() {
    getMapUnitParam(&mAngleY_m, "AngleY");
}

void SetComebackPosition::calc_() {
    AreaActionBase::calc_();
}

}  // namespace uking::action

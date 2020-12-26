#include "Game/AI/Action/actionGetUpMoveAnmDriven.h"

namespace uking::action {

GetUpMoveAnmDriven::GetUpMoveAnmDriven(const InitArg& arg) : GetUp(arg) {}

GetUpMoveAnmDriven::~GetUpMoveAnmDriven() = default;

bool GetUpMoveAnmDriven::init_(sead::Heap* heap) {
    return GetUp::init_(heap);
}

void GetUpMoveAnmDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUp::enter_(params);
}

void GetUpMoveAnmDriven::leave_() {
    GetUp::leave_();
}

void GetUpMoveAnmDriven::loadParams_() {
    GetUp::loadParams_();
    getStaticParam(&mTargetBoneName_s, "TargetBoneName");
}

void GetUpMoveAnmDriven::calc_() {
    GetUp::calc_();
}

}  // namespace uking::action

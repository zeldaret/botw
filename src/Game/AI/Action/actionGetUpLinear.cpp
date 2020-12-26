#include "Game/AI/Action/actionGetUpLinear.h"

namespace uking::action {

GetUpLinear::GetUpLinear(const InitArg& arg) : GetUpBase(arg) {}

GetUpLinear::~GetUpLinear() = default;

bool GetUpLinear::init_(sead::Heap* heap) {
    return GetUpBase::init_(heap);
}

void GetUpLinear::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUpBase::enter_(params);
}

void GetUpLinear::leave_() {
    GetUpBase::leave_();
}

void GetUpLinear::loadParams_() {
    GetUpBase::loadParams_();
    getStaticParam(&mRotCenterPos_s, "RotCenterPos");
}

void GetUpLinear::calc_() {
    GetUpBase::calc_();
}

}  // namespace uking::action

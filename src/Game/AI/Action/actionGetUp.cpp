#include "Game/AI/Action/actionGetUp.h"

namespace uking::action {

GetUp::GetUp(const InitArg& arg) : GetUpBase(arg) {}

GetUp::~GetUp() = default;

bool GetUp::init_(sead::Heap* heap) {
    return GetUpBase::init_(heap);
}

void GetUp::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUpBase::enter_(params);
}

void GetUp::leave_() {
    GetUpBase::leave_();
}

void GetUp::loadParams_() {
    GetUpBase::loadParams_();
    getStaticParam(&mRotRatio_s, "RotRatio");
}

void GetUp::calc_() {
    GetUpBase::calc_();
}

}  // namespace uking::action

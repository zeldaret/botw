#include "Game/AI/Action/actionForkEmitExpandFieldWithCreate.h"

namespace uking::action {

ForkEmitExpandFieldWithCreate::ForkEmitExpandFieldWithCreate(const InitArg& arg)
    : ForkEmitExpandField(arg) {}

ForkEmitExpandFieldWithCreate::~ForkEmitExpandFieldWithCreate() = default;

bool ForkEmitExpandFieldWithCreate::init_(sead::Heap* heap) {
    return ForkEmitExpandField::init_(heap);
}

void ForkEmitExpandFieldWithCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitExpandField::enter_(params);
}

void ForkEmitExpandFieldWithCreate::leave_() {
    ForkEmitExpandField::leave_();
}

void ForkEmitExpandFieldWithCreate::loadParams_() {
    ForkEmitExpandField::loadParams_();
    getStaticParam(&mScaleTime_s, "ScaleTime");
    getStaticParam(&mIsReuseActor_s, "IsReuseActor");
    getStaticParam(&mIsSetPartsLink_s, "IsSetPartsLink");
}

void ForkEmitExpandFieldWithCreate::calc_() {
    ForkEmitExpandField::calc_();
}

}  // namespace uking::action

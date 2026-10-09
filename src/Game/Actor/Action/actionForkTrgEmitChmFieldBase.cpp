#include "Game/Actor/Action/actionForkTrgEmitChmFieldBase.h"

namespace uking::action {

ForkTrgEmitChmFieldBase::ForkTrgEmitChmFieldBase(const InitArg& arg) : ForkEmitExpandField(arg) {}

ForkTrgEmitChmFieldBase::~ForkTrgEmitChmFieldBase() = default;

bool ForkTrgEmitChmFieldBase::init_(sead::Heap* heap) {
    return ForkEmitExpandField::init_(heap);
}

void ForkTrgEmitChmFieldBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitExpandField::enter_(params);
}

void ForkTrgEmitChmFieldBase::leave_() {
    ForkEmitExpandField::leave_();
}

void ForkTrgEmitChmFieldBase::loadParams_() {
    ForkEmitExpandField::loadParams_();
    getStaticParam(&mEmitIntervalTime_s, "EmitIntervalTime");
}

void ForkTrgEmitChmFieldBase::calc_() {
    ForkEmitExpandField::calc_();
}

}  // namespace uking::action

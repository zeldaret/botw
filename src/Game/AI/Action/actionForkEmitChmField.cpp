#include "Game/AI/Action/actionForkEmitChmField.h"

namespace uking::action {

ForkEmitChmField::ForkEmitChmField(const InitArg& arg) : ForkEmitExpandField(arg) {}

ForkEmitChmField::~ForkEmitChmField() = default;

bool ForkEmitChmField::init_(sead::Heap* heap) {
    return ForkEmitExpandField::init_(heap);
}

void ForkEmitChmField::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitExpandField::enter_(params);
}

void ForkEmitChmField::leave_() {
    ForkEmitExpandField::leave_();
}

void ForkEmitChmField::loadParams_() {
    ForkEmitExpandField::loadParams_();
    getStaticParam(&mEmitIntervalTime_s, "EmitIntervalTime");
}

void ForkEmitChmField::calc_() {
    ForkEmitExpandField::calc_();
}

}  // namespace uking::action

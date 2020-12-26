#include "Game/AI/Action/actionForkEmitChmFieldByContact.h"

namespace uking::action {

ForkEmitChmFieldByContact::ForkEmitChmFieldByContact(const InitArg& arg) : ForkEmitChmField(arg) {}

ForkEmitChmFieldByContact::~ForkEmitChmFieldByContact() = default;

bool ForkEmitChmFieldByContact::init_(sead::Heap* heap) {
    return ForkEmitChmField::init_(heap);
}

void ForkEmitChmFieldByContact::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitChmField::enter_(params);
}

void ForkEmitChmFieldByContact::leave_() {
    ForkEmitChmField::leave_();
}

void ForkEmitChmFieldByContact::loadParams_() {
    ForkEmitChmField::loadParams_();
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

void ForkEmitChmFieldByContact::calc_() {
    ForkEmitChmField::calc_();
}

}  // namespace uking::action

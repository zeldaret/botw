#include "Game/Actor/Action/actionForkEmitChmFieldByContact.h"

namespace uking::action {

ForkEmitChmFieldByContact::ForkEmitChmFieldByContact(const InitArg& arg)
    : ForkTrgEmitChmFieldBase(arg) {}

ForkEmitChmFieldByContact::~ForkEmitChmFieldByContact() = default;

bool ForkEmitChmFieldByContact::init_(sead::Heap* heap) {
    return ForkTrgEmitChmFieldBase::init_(heap);
}

void ForkEmitChmFieldByContact::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTrgEmitChmFieldBase::enter_(params);
}

void ForkEmitChmFieldByContact::leave_() {
    ForkTrgEmitChmFieldBase::leave_();
}

void ForkEmitChmFieldByContact::loadParams_() {
    ForkTrgEmitChmFieldBase::loadParams_();
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

void ForkEmitChmFieldByContact::calc_() {
    ForkTrgEmitChmFieldBase::calc_();
}

}  // namespace uking::action

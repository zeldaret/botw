#include "Game/AI/Action/actionGetUpBase.h"

namespace uking::action {

GetUpBase::GetUpBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GetUpBase::~GetUpBase() = default;

bool GetUpBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GetUpBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GetUpBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void GetUpBase::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mRootOffset_s, "RootOffset");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void GetUpBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionWaitOnObjBase.h"

namespace uking::action {

WaitOnObjBase::WaitOnObjBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitOnObjBase::~WaitOnObjBase() = default;

bool WaitOnObjBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitOnObjBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitOnObjBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitOnObjBase::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

void WaitOnObjBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

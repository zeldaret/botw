#include "Game/Actor/Action/actionForkEndByConditionBase.h"

namespace uking::action {

ForkEndByConditionBase::ForkEndByConditionBase(const InitArg& arg) : Fork(arg) {}

ForkEndByConditionBase::~ForkEndByConditionBase() = default;

bool ForkEndByConditionBase::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkEndByConditionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkEndByConditionBase::leave_() {
    Fork::leave_();
}

void ForkEndByConditionBase::loadParams_() {
    Fork::loadParams_();
}

void ForkEndByConditionBase::calc_() {
    Fork::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionSlippedBackWalkBase.h"

namespace uking::action {

SlippedBackWalkBase::SlippedBackWalkBase(const InitArg& arg) : BackWalkBase(arg) {}

SlippedBackWalkBase::~SlippedBackWalkBase() = default;

bool SlippedBackWalkBase::init_(sead::Heap* heap) {
    return BackWalkBase::init_(heap);
}

void SlippedBackWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkBase::enter_(params);
}

void SlippedBackWalkBase::leave_() {
    BackWalkBase::leave_();
}

void SlippedBackWalkBase::loadParams_() {
    BackWalkBase::loadParams_();
    getStaticParam(&mAccRatio_s, "AccRatio");
}

void SlippedBackWalkBase::calc_() {
    BackWalkBase::calc_();
}

}  // namespace uking::action

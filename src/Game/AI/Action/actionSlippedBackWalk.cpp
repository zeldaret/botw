#include "Game/AI/Action/actionSlippedBackWalk.h"

namespace uking::action {

SlippedBackWalk::SlippedBackWalk(const InitArg& arg) : SlippedBackWalkBase(arg) {}

SlippedBackWalk::~SlippedBackWalk() = default;

bool SlippedBackWalk::init_(sead::Heap* heap) {
    return SlippedBackWalkBase::init_(heap);
}

void SlippedBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    SlippedBackWalkBase::enter_(params);
}

void SlippedBackWalk::leave_() {
    SlippedBackWalkBase::leave_();
}

void SlippedBackWalk::loadParams_() {
    SlippedBackWalkBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SlippedBackWalk::calc_() {
    SlippedBackWalkBase::calc_();
}

}  // namespace uking::action

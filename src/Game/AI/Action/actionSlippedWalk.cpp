#include "Game/AI/Action/actionSlippedWalk.h"

namespace uking::action {

SlippedWalk::SlippedWalk(const InitArg& arg) : SlippedWalkBase(arg) {}

SlippedWalk::~SlippedWalk() = default;

bool SlippedWalk::init_(sead::Heap* heap) {
    return SlippedWalkBase::init_(heap);
}

void SlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    SlippedWalkBase::enter_(params);
}

void SlippedWalk::leave_() {
    SlippedWalkBase::leave_();
}

void SlippedWalk::loadParams_() {
    SlippedWalkBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SlippedWalk::calc_() {
    SlippedWalkBase::calc_();
}

}  // namespace uking::action

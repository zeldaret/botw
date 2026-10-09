#include "Game/Actor/Action/actionSlippedWalk.h"

namespace uking::action {

SlippedWalk::SlippedWalk(const InitArg& arg) : SlippedMoveBase(arg) {}

SlippedWalk::~SlippedWalk() = default;

bool SlippedWalk::init_(sead::Heap* heap) {
    return SlippedMoveBase::init_(heap);
}

void SlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    SlippedMoveBase::enter_(params);
}

void SlippedWalk::leave_() {
    SlippedMoveBase::leave_();
}

void SlippedWalk::loadParams_() {
    SlippedMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SlippedWalk::calc_() {
    SlippedMoveBase::calc_();
}

}  // namespace uking::action

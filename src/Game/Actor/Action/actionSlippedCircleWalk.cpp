#include "Game/Actor/Action/actionSlippedCircleWalk.h"

namespace uking::action {

SlippedCircleWalk::SlippedCircleWalk(const InitArg& arg) : SlippedCircleMoveBase(arg) {}

SlippedCircleWalk::~SlippedCircleWalk() = default;

bool SlippedCircleWalk::init_(sead::Heap* heap) {
    return SlippedCircleMoveBase::init_(heap);
}

void SlippedCircleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    SlippedCircleMoveBase::enter_(params);
}

void SlippedCircleWalk::leave_() {
    SlippedCircleMoveBase::leave_();
}

void SlippedCircleWalk::loadParams_() {
    SlippedCircleMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SlippedCircleWalk::calc_() {
    SlippedCircleMoveBase::calc_();
}

}  // namespace uking::action

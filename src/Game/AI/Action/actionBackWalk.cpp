#include "Game/AI/Action/actionBackWalk.h"

namespace uking::action {

BackWalk::BackWalk(const InitArg& arg) : BackWalkEx(arg) {}

BackWalk::~BackWalk() = default;

bool BackWalk::init_(sead::Heap* heap) {
    return BackWalkEx::init_(heap);
}

void BackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkEx::enter_(params);
}

void BackWalk::leave_() {
    BackWalkEx::leave_();
}

void BackWalk::loadParams_() {
    BackWalkBase::loadParams_();
}

void BackWalk::calc_() {
    BackWalkEx::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionBackWalkEx.h"

namespace uking::action {

BackWalkEx::BackWalkEx(const InitArg& arg) : BackWalkBase(arg) {}

BackWalkEx::~BackWalkEx() = default;

bool BackWalkEx::init_(sead::Heap* heap) {
    return BackWalkBase::init_(heap);
}

void BackWalkEx::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkBase::enter_(params);
}

void BackWalkEx::leave_() {
    BackWalkBase::leave_();
}

void BackWalkEx::loadParams_() {
    BackWalkBase::loadParams_();
}

void BackWalkEx::calc_() {
    BackWalkBase::calc_();
}

}  // namespace uking::action

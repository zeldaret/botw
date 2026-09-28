#include "Game/Actor/Action/actionNormalBackWalk.h"

namespace uking::action {

NormalBackWalk::NormalBackWalk(const InitArg& arg) : BackWalkBase(arg) {}

NormalBackWalk::~NormalBackWalk() = default;

bool NormalBackWalk::init_(sead::Heap* heap) {
    return BackWalkBase::init_(heap);
}

void NormalBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkBase::enter_(params);
}

void NormalBackWalk::leave_() {
    BackWalkBase::leave_();
}

void NormalBackWalk::loadParams_() {
    BackWalkBase::loadParams_();
}

void NormalBackWalk::calc_() {
    BackWalkBase::calc_();
}

}  // namespace uking::action

#include "Game/Actor/Action/actionAreaBottomTag.h"

namespace uking::action {

AreaBottomTag::AreaBottomTag(const InitArg& arg) : AreaActionBase(arg) {}

AreaBottomTag::~AreaBottomTag() = default;

bool AreaBottomTag::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void AreaBottomTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void AreaBottomTag::leave_() {
    AreaActionBase::leave_();
}

void AreaBottomTag::loadParams_() {}

void AreaBottomTag::calc_() {
    AreaActionBase::calc_();
}

}  // namespace uking::action

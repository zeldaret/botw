#include "Game/AI/Action/actionAreaBottomTag.h"

namespace uking::action {

AreaBottomTag::AreaBottomTag(const InitArg& arg) : AreaTagAction(arg) {}

AreaBottomTag::~AreaBottomTag() = default;

bool AreaBottomTag::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void AreaBottomTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void AreaBottomTag::leave_() {
    AreaTagAction::leave_();
}

void AreaBottomTag::loadParams_() {}

void AreaBottomTag::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action

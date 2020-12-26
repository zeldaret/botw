#include "Game/AI/Action/actionSetWorldRotOffsetFromTransBone.h"

namespace uking::action {

SetWorldRotOffsetFromTransBone::SetWorldRotOffsetFromTransBone(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetWorldRotOffsetFromTransBone::~SetWorldRotOffsetFromTransBone() = default;

bool SetWorldRotOffsetFromTransBone::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetWorldRotOffsetFromTransBone::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetWorldRotOffsetFromTransBone::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetWorldRotOffsetFromTransBone::loadParams_() {}

void SetWorldRotOffsetFromTransBone::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

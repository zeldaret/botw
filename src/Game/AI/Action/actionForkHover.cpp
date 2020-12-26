#include "Game/AI/Action/actionForkHover.h"

namespace uking::action {

ForkHover::ForkHover(const InitArg& arg) : HoverBase(arg) {}

ForkHover::~ForkHover() = default;

bool ForkHover::init_(sead::Heap* heap) {
    return HoverBase::init_(heap);
}

void ForkHover::enter_(ksys::act::ai::InlineParamPack* params) {
    HoverBase::enter_(params);
}

void ForkHover::leave_() {
    HoverBase::leave_();
}

void ForkHover::loadParams_() {
    HoverBase::loadParams_();
}

void ForkHover::calc_() {
    HoverBase::calc_();
}

}  // namespace uking::action

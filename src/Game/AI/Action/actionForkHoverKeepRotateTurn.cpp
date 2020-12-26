#include "Game/AI/Action/actionForkHoverKeepRotateTurn.h"

namespace uking::action {

ForkHoverKeepRotateTurn::ForkHoverKeepRotateTurn(const InitArg& arg)
    : ForkHoverKeepRotateTurnBase(arg) {}

ForkHoverKeepRotateTurn::~ForkHoverKeepRotateTurn() = default;

bool ForkHoverKeepRotateTurn::init_(sead::Heap* heap) {
    return ForkHoverKeepRotateTurnBase::init_(heap);
}

void ForkHoverKeepRotateTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkHoverKeepRotateTurnBase::enter_(params);
}

void ForkHoverKeepRotateTurn::leave_() {
    ForkHoverKeepRotateTurnBase::leave_();
}

void ForkHoverKeepRotateTurn::loadParams_() {
    ForkHoverKeepRotateTurnBase::loadParams_();
}

void ForkHoverKeepRotateTurn::calc_() {
    ForkHoverKeepRotateTurnBase::calc_();
}

}  // namespace uking::action

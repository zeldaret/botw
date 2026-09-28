#include "Game/Actor/Action/actionForkHoverKeepRotateTurn.h"

namespace uking::action {

ForkHoverKeepRotateTurn::ForkHoverKeepRotateTurn(const InitArg& arg) : ForkKeepRotateTurn(arg) {}

ForkHoverKeepRotateTurn::~ForkHoverKeepRotateTurn() = default;

bool ForkHoverKeepRotateTurn::init_(sead::Heap* heap) {
    return ForkKeepRotateTurn::init_(heap);
}

void ForkHoverKeepRotateTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkKeepRotateTurn::enter_(params);
}

void ForkHoverKeepRotateTurn::leave_() {
    ForkKeepRotateTurn::leave_();
}

void ForkHoverKeepRotateTurn::loadParams_() {
    ForkKeepRotateTurn::loadParams_();
}

void ForkHoverKeepRotateTurn::calc_() {
    ForkKeepRotateTurn::calc_();
}

}  // namespace uking::action

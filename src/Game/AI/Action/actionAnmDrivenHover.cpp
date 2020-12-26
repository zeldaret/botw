#include "Game/AI/Action/actionAnmDrivenHover.h"

namespace uking::action {

AnmDrivenHover::AnmDrivenHover(const InitArg& arg) : AnmDrivenHoverBase(arg) {}

AnmDrivenHover::~AnmDrivenHover() = default;

bool AnmDrivenHover::init_(sead::Heap* heap) {
    return AnmDrivenHoverBase::init_(heap);
}

void AnmDrivenHover::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmDrivenHoverBase::enter_(params);
}

void AnmDrivenHover::leave_() {
    AnmDrivenHoverBase::leave_();
}

void AnmDrivenHover::loadParams_() {
    AnmDrivenHoverBase::loadParams_();
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

void AnmDrivenHover::calc_() {
    AnmDrivenHoverBase::calc_();
}

}  // namespace uking::action

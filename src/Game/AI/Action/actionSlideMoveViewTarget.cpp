#include "Game/AI/Action/actionSlideMoveViewTarget.h"

namespace uking::action {

SlideMoveViewTarget::SlideMoveViewTarget(const InitArg& arg) : MoveBase(arg) {}

SlideMoveViewTarget::~SlideMoveViewTarget() = default;

bool SlideMoveViewTarget::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void SlideMoveViewTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void SlideMoveViewTarget::leave_() {
    MoveBase::leave_();
}

void SlideMoveViewTarget::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SlideMoveViewTarget::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action

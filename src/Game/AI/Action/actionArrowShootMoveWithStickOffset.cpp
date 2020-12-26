#include "Game/AI/Action/actionArrowShootMoveWithStickOffset.h"

namespace uking::action {

ArrowShootMoveWithStickOffset::ArrowShootMoveWithStickOffset(const InitArg& arg)
    : ArrowShootMove(arg) {}

ArrowShootMoveWithStickOffset::~ArrowShootMoveWithStickOffset() = default;

bool ArrowShootMoveWithStickOffset::init_(sead::Heap* heap) {
    return ArrowShootMove::init_(heap);
}

void ArrowShootMoveWithStickOffset::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
}

void ArrowShootMoveWithStickOffset::leave_() {
    ArrowShootMove::leave_();
}

void ArrowShootMoveWithStickOffset::loadParams_() {
    ArrowShootMove::loadParams_();
    getStaticParam(&mStickOffset_s, "StickOffset");
}

void ArrowShootMoveWithStickOffset::calc_() {
    ArrowShootMove::calc_();
}

}  // namespace uking::action

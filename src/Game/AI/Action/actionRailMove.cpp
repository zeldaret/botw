#include "Game/AI/Action/actionRailMove.h"

namespace uking::action {

RailMove::RailMove(const InitArg& arg) : RailMoveBase(arg) {}

RailMove::~RailMove() = default;

bool RailMove::init_(sead::Heap* heap) {
    return RailMoveBase::init_(heap);
}

void RailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveBase::enter_(params);
}

void RailMove::leave_() {
    RailMoveBase::leave_();
}

void RailMove::loadParams_() {
    RailMoveBase::loadParams_();
    getDynamicParam(&mRailName_d, "RailName");
}

void RailMove::calc_() {
    RailMoveBase::calc_();
}

}  // namespace uking::action

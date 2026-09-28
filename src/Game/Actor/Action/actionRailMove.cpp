#include "Game/Actor/Action/actionRailMove.h"

namespace uking::action {

RailMove::RailMove(const InitArg& arg) : DestPointMoveBase(arg) {}

RailMove::~RailMove() = default;

bool RailMove::init_(sead::Heap* heap) {
    return DestPointMoveBase::init_(heap);
}

void RailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    DestPointMoveBase::enter_(params);
}

void RailMove::leave_() {
    DestPointMoveBase::leave_();
}

void RailMove::loadParams_() {
    DestPointMoveBase::loadParams_();
    getDynamicParam(&mRailName_d, "RailName");
}

void RailMove::calc_() {
    DestPointMoveBase::calc_();
}

}  // namespace uking::action

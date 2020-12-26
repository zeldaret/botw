#include "Game/AI/Action/actionForkASHoldLinearMove.h"

namespace uking::action {

ForkASHoldLinearMove::ForkASHoldLinearMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASHoldLinearMove::~ForkASHoldLinearMove() = default;

bool ForkASHoldLinearMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASHoldLinearMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASHoldLinearMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASHoldLinearMove::loadParams_() {
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mRotRestRatio_s, "RotRestRatio");
    getStaticParam(&mPosRestRatio_s, "PosRestRatio");
    getStaticParam(&mMoveDir_s, "MoveDir");
    getStaticParam(&mGravityTransReduce_s, "GravityTransReduce");
}

void ForkASHoldLinearMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionGanonMove.h"

namespace uking::action {

GanonMove::GanonMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonMove::~GanonMove() = default;

bool GanonMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonMove::loadParams_() {
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveAccel_s, "MoveAccel");
    getStaticParam(&mAvoidMoveSpeed_s, "AvoidMoveSpeed");
    getStaticParam(&mAvoidMoveAccel_s, "AvoidMoveAccel");
    getStaticParam(&mIsUpEqualGravity_s, "IsUpEqualGravity");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mDstPos_d, "DstPos");
}

void GanonMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

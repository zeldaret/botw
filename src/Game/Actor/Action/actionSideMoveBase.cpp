#include "Game/Actor/Action/actionSideMoveBase.h"

namespace uking::action {

SideMoveBase::SideMoveBase(const InitArg& arg) : MoveBase(arg) {}

SideMoveBase::~SideMoveBase() = default;

bool SideMoveBase::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void SideMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void SideMoveBase::leave_() {
    MoveBase::leave_();
}

void SideMoveBase::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mLeftMove_s, "LeftMove");
}

void SideMoveBase::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action

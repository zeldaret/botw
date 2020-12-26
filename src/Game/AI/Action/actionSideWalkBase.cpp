#include "Game/AI/Action/actionSideWalkBase.h"

namespace uking::action {

SideWalkBase::SideWalkBase(const InitArg& arg) : MoveBase(arg) {}

SideWalkBase::~SideWalkBase() = default;

bool SideWalkBase::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void SideWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void SideWalkBase::leave_() {
    MoveBase::leave_();
}

void SideWalkBase::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mLeftMove_s, "LeftMove");
}

void SideWalkBase::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action

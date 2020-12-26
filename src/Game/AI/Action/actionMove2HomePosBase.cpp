#include "Game/AI/Action/actionMove2HomePosBase.h"

namespace uking::action {

Move2HomePosBase::Move2HomePosBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Move2HomePosBase::~Move2HomePosBase() = default;

bool Move2HomePosBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Move2HomePosBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Move2HomePosBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void Move2HomePosBase::loadParams_() {
    getStaticParam(&mIsReturn_s, "IsReturn");
    getDynamicParam(&mDynMoveDis_d, "DynMoveDis");
    getDynamicParam(&mDynMoveSpeed_d, "DynMoveSpeed");
}

void Move2HomePosBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

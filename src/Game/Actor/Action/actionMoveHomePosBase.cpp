#include "Game/Actor/Action/actionMoveHomePosBase.h"

namespace uking::action {

MoveHomePosBase::MoveHomePosBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveHomePosBase::~MoveHomePosBase() = default;

bool MoveHomePosBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveHomePosBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MoveHomePosBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveHomePosBase::loadParams_() {
    getStaticParam(&mIsReturn_s, "IsReturn");
    getDynamicParam(&mDynMoveDis_d, "DynMoveDis");
    getDynamicParam(&mDynMoveSpeed_d, "DynMoveSpeed");
}

void MoveHomePosBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/Actor/Action/actionSideWalk.h"

namespace uking::action {

SideWalk::SideWalk(const InitArg& arg) : SideMoveBase(arg) {}

SideWalk::~SideWalk() = default;

bool SideWalk::init_(sead::Heap* heap) {
    return SideMoveBase::init_(heap);
}

void SideWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    SideMoveBase::enter_(params);
}

void SideWalk::leave_() {
    SideMoveBase::leave_();
}

void SideWalk::loadParams_() {
    SideMoveBase::loadParams_();
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void SideWalk::calc_() {
    SideMoveBase::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionFollowDungeonRotate.h"

namespace uking::action {

FollowDungeonRotate::FollowDungeonRotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FollowDungeonRotate::~FollowDungeonRotate() = default;

bool FollowDungeonRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FollowDungeonRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FollowDungeonRotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void FollowDungeonRotate::loadParams_() {
    getStaticParam(&mIsChangeableOnEnter_s, "IsChangeableOnEnter");
    getStaticParam(&mIsSetNoHit_s, "IsSetNoHit");
}

void FollowDungeonRotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

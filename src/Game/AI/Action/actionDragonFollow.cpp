#include "Game/AI/Action/actionDragonFollow.h"

namespace uking::action {

DragonFollow::DragonFollow(const InitArg& arg) : FollowChallenge(arg) {}

DragonFollow::~DragonFollow() = default;

bool DragonFollow::init_(sead::Heap* heap) {
    return FollowChallenge::init_(heap);
}

void DragonFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    FollowChallenge::enter_(params);
}

void DragonFollow::leave_() {
    FollowChallenge::leave_();
}

void DragonFollow::loadParams_() {
    FollowChallenge::loadParams_();
    getStaticParam(&mDungeonName_s, "DungeonName");
}

void DragonFollow::calc_() {
    FollowChallenge::calc_();
}

}  // namespace uking::action

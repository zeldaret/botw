#include "Game/Actor/Action/actionDragonFollow.h"

namespace uking::action {

DragonFollow::DragonFollow(const InitArg& arg) : AppearFollowChallenge(arg) {}

DragonFollow::~DragonFollow() = default;

bool DragonFollow::init_(sead::Heap* heap) {
    return AppearFollowChallenge::init_(heap);
}

void DragonFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearFollowChallenge::enter_(params);
}

void DragonFollow::leave_() {
    AppearFollowChallenge::leave_();
}

void DragonFollow::loadParams_() {
    AppearFollowChallenge::loadParams_();
    getStaticParam(&mDungeonName_s, "DungeonName");
}

void DragonFollow::calc_() {
    AppearFollowChallenge::calc_();
}

}  // namespace uking::action

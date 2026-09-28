#include "Game/Actor/Action/actionAppearFollowChallenge.h"

namespace uking::action {

AppearFollowChallenge::AppearFollowChallenge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearFollowChallenge::~AppearFollowChallenge() = default;

bool AppearFollowChallenge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearFollowChallenge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AppearFollowChallenge::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearFollowChallenge::loadParams_() {
    getMapUnitParam(&mGimmickTimeLimit_m, "GimmickTimeLimit");
    getMapUnitParam(&mIsBillboard_m, "IsBillboard");
}

void AppearFollowChallenge::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

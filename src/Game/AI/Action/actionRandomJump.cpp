#include "Game/AI/Action/actionRandomJump.h"

namespace uking::action {

RandomJump::RandomJump(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RandomJump::~RandomJump() = default;

bool RandomJump::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RandomJump::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RandomJump::leave_() {
    ksys::act::ai::Action::leave_();
}

void RandomJump::loadParams_() {
    getStaticParam(&mAngleLimit_s, "AngleLimit");
    getStaticParam(&mHeightMin_s, "HeightMin");
    getStaticParam(&mHeightMaxOffset_s, "HeightMaxOffset");
    getStaticParam(&mDistanceMin_s, "DistanceMin");
    getStaticParam(&mDistanceMaxOffset_s, "DistanceMaxOffset");
    getStaticParam(&mIsReturnByHitWall_s, "IsReturnByHitWall");
    getStaticParam(&mASName_s, "ASName");
}

void RandomJump::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionForkNoHitGroundCrawl.h"

namespace uking::action {

ForkNoHitGroundCrawl::ForkNoHitGroundCrawl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkNoHitGroundCrawl::~ForkNoHitGroundCrawl() = default;

bool ForkNoHitGroundCrawl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkNoHitGroundCrawl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkNoHitGroundCrawl::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkNoHitGroundCrawl::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mEndRadius_s, "EndRadius");
}

void ForkNoHitGroundCrawl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

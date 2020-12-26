#include "Game/AI/Action/actionSiteBossDie.h"

namespace uking::action {

SiteBossDie::SiteBossDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossDie::~SiteBossDie() = default;

bool SiteBossDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossDie::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossDie::loadParams_() {
    getStaticParam(&mWarpWaitTime_s, "WarpWaitTime");
    getStaticParam(&mIsUseYAxisSignal_s, "IsUseYAxisSignal");
}

void SiteBossDie::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

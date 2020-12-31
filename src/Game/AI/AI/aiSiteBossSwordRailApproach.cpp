#include "Game/AI/AI/aiSiteBossSwordRailApproach.h"

namespace uking::ai {

SiteBossSwordRailApproach::SiteBossSwordRailApproach(const InitArg& arg)
    : SiteBossSwordApproachRoot(arg) {}

SiteBossSwordRailApproach::~SiteBossSwordRailApproach() = default;

bool SiteBossSwordRailApproach::init_(sead::Heap* heap) {
    return SiteBossSwordApproachRoot::init_(heap);
}

void SiteBossSwordRailApproach::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossSwordApproachRoot::enter_(params);
}

void SiteBossSwordRailApproach::leave_() {
    SiteBossSwordApproachRoot::leave_();
}

void SiteBossSwordRailApproach::loadParams_() {
    SiteBossSwordApproachRoot::loadParams_();
    getDynamicParam(&mIsResetOldMoveIdx_d, "IsResetOldMoveIdx");
}

}  // namespace uking::ai

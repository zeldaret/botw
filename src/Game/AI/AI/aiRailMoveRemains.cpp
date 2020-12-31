#include "Game/AI/AI/aiRailMoveRemains.h"

namespace uking::ai {

RailMoveRemains::RailMoveRemains(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RailMoveRemains::~RailMoveRemains() = default;

bool RailMoveRemains::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RailMoveRemains::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RailMoveRemains::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMoveRemains::loadParams_() {
    getStaticParam(&mReactivateTime_s, "ReactivateTime");
    getStaticParam(&mFrontCheckMinDist_s, "FrontCheckMinDist");
    getStaticParam(&mFrontDirUpdateInterval_s, "FrontDirUpdateInterval");
    getStaticParam(&mSpeedScale_s, "SpeedScale");
    getStaticParam(&mInitPosByRailRatio_s, "InitPosByRailRatio");
}

}  // namespace uking::ai

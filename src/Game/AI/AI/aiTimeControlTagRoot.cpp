#include "Game/AI/AI/aiTimeControlTagRoot.h"

namespace uking::ai {

TimeControlTagRoot::TimeControlTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TimeControlTagRoot::~TimeControlTagRoot() = default;

bool TimeControlTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TimeControlTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TimeControlTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TimeControlTagRoot::loadParams_() {
    getMapUnitParam(&mStartTime_m, "StartTime");
    getMapUnitParam(&mEndTime_m, "EndTime");
    getMapUnitParam(&mStartTimeMinute_m, "StartTimeMinute");
    getMapUnitParam(&mEndTimeMinute_m, "EndTimeMinute");
    getMapUnitParam(&mIsDirectTime_m, "IsDirectTime");
    getMapUnitParam(&mIsMorningA_m, "IsMorningA");
    getMapUnitParam(&mIsMorningB_m, "IsMorningB");
    getMapUnitParam(&mIsNoonA_m, "IsNoonA");
    getMapUnitParam(&mIsNoonB_m, "IsNoonB");
    getMapUnitParam(&mIsEveningA_m, "IsEveningA");
    getMapUnitParam(&mIsEveningB_m, "IsEveningB");
    getMapUnitParam(&mIsNightA_m, "IsNightA");
    getMapUnitParam(&mIsNightB_m, "IsNightB");
}

}  // namespace uking::ai

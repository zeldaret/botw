#include "Game/AI/AI/aiInsectEscape.h"

namespace uking::ai {

InsectEscape::InsectEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InsectEscape::~InsectEscape() = default;

bool InsectEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InsectEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void InsectEscape::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InsectEscape::loadParams_() {
    getStaticParam(&mRunAwayDistanceMax_s, "RunAwayDistanceMax");
    getStaticParam(&mRunAwayDistanceMin_s, "RunAwayDistanceMin");
    getStaticParam(&mRunAwayHeightOffset_s, "RunAwayHeightOffset");
    getStaticParam(&mAllowRandAngleVertical_s, "AllowRandAngleVertical");
    getStaticParam(&mAllowRandAngleHorizontal_s, "AllowRandAngleHorizontal");
    getStaticParam(&mInWater_s, "InWater");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

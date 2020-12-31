#include "Game/AI/AI/aiSiteBossBlowOff.h"

namespace uking::ai {

SiteBossBlowOff::SiteBossBlowOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossBlowOff::~SiteBossBlowOff() = default;

bool SiteBossBlowOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossBlowOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossBlowOff::loadParams_() {
    getDynamicParam(&mIsPlayDamageAnm_d, "IsPlayDamageAnm");
}

}  // namespace uking::ai

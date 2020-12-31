#include "Game/AI/AI/aiSiteBossBowChildDeviceRoot.h"

namespace uking::ai {

SiteBossBowChildDeviceRoot::SiteBossBowChildDeviceRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossBowChildDeviceRoot::~SiteBossBowChildDeviceRoot() = default;

bool SiteBossBowChildDeviceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossBowChildDeviceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossBowChildDeviceRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossBowChildDeviceRoot::loadParams_() {
    getStaticParam(&mXRotateSpeed_s, "XRotateSpeed");
    getStaticParam(&mSlowRate_s, "SlowRate");
    getMapUnitParam(&mCount_m, "Count");
}

}  // namespace uking::ai

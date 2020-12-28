#include "Game/AI/Action/actionGuardianMiniLineBeam.h"

namespace uking::action {

GuardianMiniLineBeam::GuardianMiniLineBeam(const InitArg& arg) : SimpleLineBeam(arg) {}

GuardianMiniLineBeam::~GuardianMiniLineBeam() = default;

void GuardianMiniLineBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLineBeam::enter_(params);
}

void GuardianMiniLineBeam::loadParams_() {
    SimpleLineBeam::loadParams_();
    getStaticParam(&mIceBlockBreakTime_s, "IceBlockBreakTime");
}

void GuardianMiniLineBeam::calc_() {
    SimpleLineBeam::calc_();
}

}  // namespace uking::action

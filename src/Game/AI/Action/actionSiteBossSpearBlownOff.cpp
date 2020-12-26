#include "Game/AI/Action/actionSiteBossSpearBlownOff.h"

namespace uking::action {

SiteBossSpearBlownOff::SiteBossSpearBlownOff(const InitArg& arg) : SiteBossBowBlowOff(arg) {}

SiteBossSpearBlownOff::~SiteBossSpearBlownOff() = default;

bool SiteBossSpearBlownOff::init_(sead::Heap* heap) {
    return SiteBossBowBlowOff::init_(heap);
}

void SiteBossSpearBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossBowBlowOff::enter_(params);
}

void SiteBossSpearBlownOff::leave_() {
    SiteBossBowBlowOff::leave_();
}

void SiteBossSpearBlownOff::loadParams_() {
    SiteBossBowBlowOff::loadParams_();
    getStaticParam(&mDownTimeAtLater_s, "DownTimeAtLater");
}

void SiteBossSpearBlownOff::calc_() {
    SiteBossBowBlowOff::calc_();
}

}  // namespace uking::action

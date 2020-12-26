#include "Game/AI/Action/actionSiteBossSwordBlowOff.h"

namespace uking::action {

SiteBossSwordBlowOff::SiteBossSwordBlowOff(const InitArg& arg) : SiteBossBowBlowOff(arg) {}

SiteBossSwordBlowOff::~SiteBossSwordBlowOff() = default;

bool SiteBossSwordBlowOff::init_(sead::Heap* heap) {
    return SiteBossBowBlowOff::init_(heap);
}

void SiteBossSwordBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossBowBlowOff::enter_(params);
}

void SiteBossSwordBlowOff::leave_() {
    SiteBossBowBlowOff::leave_();
}

void SiteBossSwordBlowOff::loadParams_() {
    SiteBossBowBlowOff::loadParams_();
}

void SiteBossSwordBlowOff::calc_() {
    SiteBossBowBlowOff::calc_();
}

}  // namespace uking::action

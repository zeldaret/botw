#include "Game/AI/Action/actionSiteBossBlowOff.h"

namespace uking::action {

SiteBossBlowOff::SiteBossBlowOff(const InitArg& arg) : BlownOff(arg) {}

SiteBossBlowOff::~SiteBossBlowOff() = default;

bool SiteBossBlowOff::init_(sead::Heap* heap) {
    return BlownOff::init_(heap);
}

void SiteBossBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
}

void SiteBossBlowOff::leave_() {
    BlownOff::leave_();
}

void SiteBossBlowOff::loadParams_() {
    BlownOff::loadParams_();
}

void SiteBossBlowOff::calc_() {
    BlownOff::calc_();
}

}  // namespace uking::action

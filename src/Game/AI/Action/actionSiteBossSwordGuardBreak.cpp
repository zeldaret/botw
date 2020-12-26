#include "Game/AI/Action/actionSiteBossSwordGuardBreak.h"

namespace uking::action {

SiteBossSwordGuardBreak::SiteBossSwordGuardBreak(const InitArg& arg) : OnetimeStopASPlay(arg) {}

SiteBossSwordGuardBreak::~SiteBossSwordGuardBreak() = default;

bool SiteBossSwordGuardBreak::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void SiteBossSwordGuardBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void SiteBossSwordGuardBreak::leave_() {
    OnetimeStopASPlay::leave_();
}

void SiteBossSwordGuardBreak::loadParams_() {
    OnetimeStopASPlay::loadParams_();
}

void SiteBossSwordGuardBreak::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action

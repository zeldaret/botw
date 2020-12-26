#include "Game/AI/Action/actionSiteBossSwordGuard.h"

namespace uking::action {

SiteBossSwordGuard::SiteBossSwordGuard(const InitArg& arg) : Guard(arg) {}

SiteBossSwordGuard::~SiteBossSwordGuard() = default;

bool SiteBossSwordGuard::init_(sead::Heap* heap) {
    return Guard::init_(heap);
}

void SiteBossSwordGuard::enter_(ksys::act::ai::InlineParamPack* params) {
    Guard::enter_(params);
}

void SiteBossSwordGuard::leave_() {
    Guard::leave_();
}

void SiteBossSwordGuard::loadParams_() {
    Guard::loadParams_();
}

void SiteBossSwordGuard::calc_() {
    Guard::calc_();
}

}  // namespace uking::action

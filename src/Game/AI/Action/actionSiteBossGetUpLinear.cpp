#include "Game/AI/Action/actionSiteBossGetUpLinear.h"

namespace uking::action {

SiteBossGetUpLinear::SiteBossGetUpLinear(const InitArg& arg) : GetUpLinear(arg) {}

SiteBossGetUpLinear::~SiteBossGetUpLinear() = default;

bool SiteBossGetUpLinear::init_(sead::Heap* heap) {
    return GetUpLinear::init_(heap);
}

void SiteBossGetUpLinear::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUpLinear::enter_(params);
}

void SiteBossGetUpLinear::leave_() {
    GetUpLinear::leave_();
}

void SiteBossGetUpLinear::loadParams_() {
    GetUpLinear::loadParams_();
    getStaticParam(&mIsRestoreRigidBody_s, "IsRestoreRigidBody");
    getStaticParam(&mForceRecoverOffset_s, "ForceRecoverOffset");
    getStaticParam(&mForceRecoverDist_s, "ForceRecoverDist");
}

void SiteBossGetUpLinear::calc_() {
    GetUpLinear::calc_();
}

}  // namespace uking::action

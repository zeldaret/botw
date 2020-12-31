#include "Game/AI/AI/aiSiteBossReflectArrowRoot.h"

namespace uking::ai {

SiteBossReflectArrowRoot::SiteBossReflectArrowRoot(const InitArg& arg)
    : SiteBossShootNormalArrowRoot(arg) {}

SiteBossReflectArrowRoot::~SiteBossReflectArrowRoot() = default;

bool SiteBossReflectArrowRoot::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrowRoot::init_(heap);
}

void SiteBossReflectArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrowRoot::enter_(params);
}

void SiteBossReflectArrowRoot::leave_() {
    SiteBossShootNormalArrowRoot::leave_();
}

void SiteBossReflectArrowRoot::loadParams_() {
    SiteBossShootNormalArrowRoot::loadParams_();
    getDynamicParam(&mIsReflectAmongChild_d, "IsReflectAmongChild");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai

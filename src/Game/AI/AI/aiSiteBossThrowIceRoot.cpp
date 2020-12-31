#include "Game/AI/AI/aiSiteBossThrowIceRoot.h"

namespace uking::ai {

SiteBossThrowIceRoot::SiteBossThrowIceRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossThrowIceRoot::~SiteBossThrowIceRoot() = default;

bool SiteBossThrowIceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossThrowIceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossThrowIceRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossThrowIceRoot::loadParams_() {
    getStaticParam(&mIgnitionNum_s, "IgnitionNum");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai

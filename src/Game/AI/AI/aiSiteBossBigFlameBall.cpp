#include "Game/AI/AI/aiSiteBossBigFlameBall.h"

namespace uking::ai {

SiteBossBigFlameBall::SiteBossBigFlameBall(const InitArg& arg) : SiteBossFlameBall(arg) {}

SiteBossBigFlameBall::~SiteBossBigFlameBall() = default;

bool SiteBossBigFlameBall::init_(sead::Heap* heap) {
    return SiteBossFlameBall::init_(heap);
}

void SiteBossBigFlameBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossFlameBall::enter_(params);
}

void SiteBossBigFlameBall::leave_() {
    SiteBossFlameBall::leave_();
}

void SiteBossBigFlameBall::loadParams_() {
    SiteBossFlameBall::loadParams_();
    getStaticParam(&mDestOffset_s, "DestOffset");
    getStaticParam(&mDestOffset1_s, "DestOffset1");
    getMapUnitParam(&mSpeed_m, "Speed");
    getMapUnitParam(&mRotOffset_m, "RotOffset");
}

}  // namespace uking::ai

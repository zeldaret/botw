#include "Game/AI/AI/aiSiteBossBowRoot.h"

namespace uking::ai {

SiteBossBowRoot::SiteBossBowRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossBowRoot::~SiteBossBowRoot() = default;

bool SiteBossBowRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossBowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
}

void SiteBossBowRoot::leave_() {
    SiteBossRoot::leave_();
}

void SiteBossBowRoot::loadParams_() {
    SiteBossRoot::loadParams_();
    getStaticParam(&mArrowRainAttackPower_s, "ArrowRainAttackPower");
    getStaticParam(&mAtMinPower_s, "AtMinPower");
    getStaticParam(&mReflectArrowAttackPower_s, "ReflectArrowAttackPower");
    getStaticParam(&mDemoName_s, "DemoName");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiSiteBossSwordRoot.h"

namespace uking::ai {

SiteBossSwordRoot::SiteBossSwordRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossSwordRoot::~SiteBossSwordRoot() = default;

bool SiteBossSwordRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossSwordRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
}

void SiteBossSwordRoot::leave_() {
    SiteBossRoot::leave_();
}

void SiteBossSwordRoot::loadParams_() {
    SiteBossRoot::loadParams_();
}

}  // namespace uking::ai

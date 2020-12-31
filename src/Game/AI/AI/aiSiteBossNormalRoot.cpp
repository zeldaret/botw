#include "Game/AI/AI/aiSiteBossNormalRoot.h"

namespace uking::ai {

SiteBossNormalRoot::SiteBossNormalRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossNormalRoot::~SiteBossNormalRoot() = default;

bool SiteBossNormalRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossNormalRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossNormalRoot::loadParams_() {}

}  // namespace uking::ai

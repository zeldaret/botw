#include "Game/AI/AI/aiSiteBossSmallDamageRoot.h"

namespace uking::ai {

SiteBossSmallDamageRoot::SiteBossSmallDamageRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSmallDamageRoot::~SiteBossSmallDamageRoot() = default;

bool SiteBossSmallDamageRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSmallDamageRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSmallDamageRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSmallDamageRoot::loadParams_() {}

}  // namespace uking::ai

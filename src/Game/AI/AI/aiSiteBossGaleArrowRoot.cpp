#include "Game/AI/AI/aiSiteBossGaleArrowRoot.h"

namespace uking::ai {

SiteBossGaleArrowRoot::SiteBossGaleArrowRoot(const InitArg& arg) : WithoutWeaponArrow(arg) {}

SiteBossGaleArrowRoot::~SiteBossGaleArrowRoot() = default;

bool SiteBossGaleArrowRoot::init_(sead::Heap* heap) {
    return WithoutWeaponArrow::init_(heap);
}

void SiteBossGaleArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WithoutWeaponArrow::enter_(params);
}

void SiteBossGaleArrowRoot::leave_() {
    WithoutWeaponArrow::leave_();
}

void SiteBossGaleArrowRoot::loadParams_() {
    WithoutWeaponArrow::loadParams_();
}

}  // namespace uking::ai

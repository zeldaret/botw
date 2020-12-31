#include "Game/AI/AI/aiSiteBossAttackRoot.h"

namespace uking::ai {

SiteBossAttackRoot::SiteBossAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossAttackRoot::~SiteBossAttackRoot() = default;

bool SiteBossAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossAttackRoot::loadParams_() {
    getStaticParam(&mEquipWeapon_s, "EquipWeapon");
}

}  // namespace uking::ai

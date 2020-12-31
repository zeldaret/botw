#include "Game/AI/AI/aiSiteBossSwordWeapon.h"

namespace uking::ai {

SiteBossSwordWeapon::SiteBossSwordWeapon(const InitArg& arg) : ChemicalWeaponRoot(arg) {}

SiteBossSwordWeapon::~SiteBossSwordWeapon() = default;

bool SiteBossSwordWeapon::init_(sead::Heap* heap) {
    return ChemicalWeaponRoot::init_(heap);
}

void SiteBossSwordWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalWeaponRoot::enter_(params);
}

void SiteBossSwordWeapon::leave_() {
    ChemicalWeaponRoot::leave_();
}

void SiteBossSwordWeapon::loadParams_() {
    WeaponRootAI::loadParams_();
}

}  // namespace uking::ai

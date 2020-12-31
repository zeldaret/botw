#include "Game/AI/AI/aiGuardianMiniChangeWeapon.h"

namespace uking::ai {

GuardianMiniChangeWeapon::GuardianMiniChangeWeapon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniChangeWeapon::~GuardianMiniChangeWeapon() = default;

bool GuardianMiniChangeWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianMiniChangeWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMiniChangeWeapon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniChangeWeapon::loadParams_() {
    getStaticParam(&mRotValue_s, "RotValue");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mDamageNodeName_s, "DamageNodeName");
    getStaticParam(&mDamageASName_s, "DamageASName");
}

}  // namespace uking::ai

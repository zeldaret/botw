#include "Game/AI/AI/aiLastBossRoot.h"

namespace uking::ai {

LastBossRoot::LastBossRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossRoot::~LastBossRoot() = default;

bool LastBossRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossRoot::loadParams_() {
    getStaticParam(&mForceRecoverHitMax_s, "ForceRecoverHitMax");
    getStaticParam(&mForceRecoverDamageMax_s, "ForceRecoverDamageMax");
    getStaticParam(&mAddForceRecoverHitNum_s, "AddForceRecoverHitNum");
    getStaticParam(&mAddForceRecoverDamage_s, "AddForceRecoverDamage");
    getStaticParam(&mAuraHPRate_s, "AuraHPRate");
    getStaticParam(&mAuraDemoName_s, "AuraDemoName");
    getStaticParam(&mAuraEntryName_s, "AuraEntryName");
    getStaticParam(&mAuraWallEntry_s, "AuraWallEntry");
    getStaticParam(&mAuraDemoDownEntry_s, "AuraDemoDownEntry");
}

}  // namespace uking::ai

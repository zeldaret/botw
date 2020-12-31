#include "Game/AI/AI/aiSiteBossSpearThrow.h"

namespace uking::ai {

SiteBossSpearThrow::SiteBossSpearThrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSpearThrow::~SiteBossSpearThrow() = default;

bool SiteBossSpearThrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSpearThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSpearThrow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSpearThrow::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMnDamage_s, "AtMnDamage");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

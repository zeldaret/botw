#include "Game/AI/AI/aiRapidAttackAllowSelect.h"

namespace uking::ai {

RapidAttackAllowSelect::RapidAttackAllowSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RapidAttackAllowSelect::~RapidAttackAllowSelect() = default;

bool RapidAttackAllowSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RapidAttackAllowSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RapidAttackAllowSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RapidAttackAllowSelect::loadParams_() {
    getStaticParam(&mAttackNum_s, "AttackNum");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai

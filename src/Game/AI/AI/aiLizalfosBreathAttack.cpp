#include "Game/AI/AI/aiLizalfosBreathAttack.h"

namespace uking::ai {

LizalfosBreathAttack::LizalfosBreathAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LizalfosBreathAttack::~LizalfosBreathAttack() = default;

void LizalfosBreathAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LizalfosBreathAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LizalfosBreathAttack::loadParams_() {
    getStaticParam(&mMinAttackTimeForTired_s, "MinAttackTimeForTired");
    getStaticParam(&mMinTiredTime_s, "MinTiredTime");
    getStaticParam(&mTiredTimeRate_s, "TiredTimeRate");
}

}  // namespace uking::ai

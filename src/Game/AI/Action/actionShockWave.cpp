#include "Game/AI/Action/actionShockWave.h"

namespace uking::action {

ShockWave::ShockWave(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShockWave::~ShockWave() = default;

bool ShockWave::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShockWave::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ShockWave::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShockWave::loadParams_() {
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackAttr_m, "AttackAttr");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mIsReuseActor_m, "IsReuseActor");
}

void ShockWave::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

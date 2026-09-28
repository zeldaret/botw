#include "Game/Actor/Action/actionEmitAttackBase.h"

namespace uking::action {

EmitAttackBase::EmitAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EmitAttackBase::~EmitAttackBase() = default;

bool EmitAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EmitAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EmitAttackBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void EmitAttackBase::loadParams_() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mAttackMinPower_s, "AttackMinPower");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mRange_m, "Range");
    getMapUnitParam(&mRigidBodyName_m, "RigidBodyName");
}

void EmitAttackBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

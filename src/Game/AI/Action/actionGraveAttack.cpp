#include "Game/AI/Action/actionGraveAttack.h"

namespace uking::action {

GraveAttack::GraveAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GraveAttack::~GraveAttack() = default;

bool GraveAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GraveAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GraveAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void GraveAttack::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mKeepTime_s, "KeepTime");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
}

void GraveAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

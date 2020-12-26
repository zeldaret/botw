#include "Game/AI/Action/actionGiantAttackWithAS.h"

namespace uking::action {

GiantAttackWithAS::GiantAttackWithAS(const InitArg& arg) : GiantAttack(arg) {}

GiantAttackWithAS::~GiantAttackWithAS() = default;

bool GiantAttackWithAS::init_(sead::Heap* heap) {
    return GiantAttack::init_(heap);
}

void GiantAttackWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantAttack::enter_(params);
}

void GiantAttackWithAS::leave_() {
    GiantAttack::leave_();
}

void GiantAttackWithAS::loadParams_() {
    GiantAttack::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void GiantAttackWithAS::calc_() {
    GiantAttack::calc_();
}

}  // namespace uking::action

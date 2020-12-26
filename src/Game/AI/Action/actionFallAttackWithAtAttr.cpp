#include "Game/AI/Action/actionFallAttackWithAtAttr.h"

namespace uking::action {

FallAttackWithAtAttr::FallAttackWithAtAttr(const InitArg& arg) : FallAttack(arg) {}

FallAttackWithAtAttr::~FallAttackWithAtAttr() = default;

bool FallAttackWithAtAttr::init_(sead::Heap* heap) {
    return FallAttack::init_(heap);
}

void FallAttackWithAtAttr::enter_(ksys::act::ai::InlineParamPack* params) {
    FallAttack::enter_(params);
}

void FallAttackWithAtAttr::leave_() {
    FallAttack::leave_();
}

void FallAttackWithAtAttr::loadParams_() {
    FallAttack::loadParams_();
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mAtAttrNoWeapon_s, "AtAttrNoWeapon");
}

void FallAttackWithAtAttr::calc_() {
    FallAttack::calc_();
}

}  // namespace uking::action

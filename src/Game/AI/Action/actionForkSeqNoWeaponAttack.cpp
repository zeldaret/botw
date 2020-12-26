#include "Game/AI/Action/actionForkSeqNoWeaponAttack.h"

namespace uking::action {

ForkSeqNoWeaponAttack::ForkSeqNoWeaponAttack(const InitArg& arg)
    : ForkAttackWithWeaponOrWithout(arg) {}

ForkSeqNoWeaponAttack::~ForkSeqNoWeaponAttack() = default;

bool ForkSeqNoWeaponAttack::init_(sead::Heap* heap) {
    return ForkAttackWithWeaponOrWithout::init_(heap);
}

void ForkSeqNoWeaponAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAttackWithWeaponOrWithout::enter_(params);
}

void ForkSeqNoWeaponAttack::leave_() {
    ForkAttackWithWeaponOrWithout::leave_();
}

void ForkSeqNoWeaponAttack::loadParams_() {
    ForkAttackWithWeaponOrWithout::loadParams_();
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mIsImpulseLarge_s, "IsImpulseLarge");
    // FIXME: CALL _ZNK4sead22BufferedSafeStringBaseIcE22assureTerminationImpl_Ev @ 0x7100b0ce00
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
    // FIXME: CALL sub_7100B0C35C @ 0x7100b0c35c
    // FIXME: CALL _ZN4sead14PrintFormatterlsEPKc @ 0x7100b0bfd8
    // FIXME: CALL _ZN4sead14PrintFormatter20proceedToFormatMark_EPc @ 0x7100b0bde0
    // FIXME: CALL _ZN4sead14PrintFormatter5flushEv @ 0x7100b0bd94
    // FIXME: CALL sead__PrintFormatter__x @ 0x7100b0c528
}

void ForkSeqNoWeaponAttack::calc_() {
    ForkAttackWithWeaponOrWithout::calc_();
}

}  // namespace uking::action

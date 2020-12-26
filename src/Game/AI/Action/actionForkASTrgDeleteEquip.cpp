#include "Game/AI/Action/actionForkASTrgDeleteEquip.h"

namespace uking::action {

ForkASTrgDeleteEquip::ForkASTrgDeleteEquip(const InitArg& arg) : ForkASTrgDelete(arg) {}

ForkASTrgDeleteEquip::~ForkASTrgDeleteEquip() = default;

bool ForkASTrgDeleteEquip::init_(sead::Heap* heap) {
    return ForkASTrgDelete::init_(heap);
}

void ForkASTrgDeleteEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgDelete::enter_(params);
}

void ForkASTrgDeleteEquip::leave_() {
    ForkASTrgDelete::leave_();
}

void ForkASTrgDeleteEquip::loadParams_() {
    ForkASTrgDelete::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void ForkASTrgDeleteEquip::calc_() {
    ForkASTrgDelete::calc_();
}

}  // namespace uking::action

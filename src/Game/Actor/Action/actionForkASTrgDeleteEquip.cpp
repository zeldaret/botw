#include "Game/Actor/Action/actionForkASTrgDeleteEquip.h"

namespace uking::action {

ForkASTrgDeleteEquip::ForkASTrgDeleteEquip(const InitArg& arg) : ForkASTrgDelete(arg) {}

ForkASTrgDeleteEquip::~ForkASTrgDeleteEquip() = default;

void ForkASTrgDeleteEquip::loadParams_() {
    ForkASTrgDelete::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::action

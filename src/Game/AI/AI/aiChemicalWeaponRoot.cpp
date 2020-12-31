#include "Game/AI/AI/aiChemicalWeaponRoot.h"

namespace uking::ai {

ChemicalWeaponRoot::ChemicalWeaponRoot(const InitArg& arg) : WeaponRootAI(arg) {}

ChemicalWeaponRoot::~ChemicalWeaponRoot() = default;

void ChemicalWeaponRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
}

}  // namespace uking::ai

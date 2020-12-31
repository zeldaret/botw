#include "Game/AI/AI/aiChemicalGiantArmorRoot.h"

namespace uking::ai {

ChemicalGiantArmorRoot::ChemicalGiantArmorRoot(const InitArg& arg) : GiantArmorRoot(arg) {}

ChemicalGiantArmorRoot::~ChemicalGiantArmorRoot() = default;

bool ChemicalGiantArmorRoot::init_(sead::Heap* heap) {
    return GiantArmorRoot::init_(heap);
}

void ChemicalGiantArmorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantArmorRoot::enter_(params);
}

void ChemicalGiantArmorRoot::leave_() {
    GiantArmorRoot::leave_();
}

void ChemicalGiantArmorRoot::loadParams_() {
    GiantArmorRoot::loadParams_();
    getStaticParam(&mElectricTime_s, "ElectricTime");
    getStaticParam(&mElectricDamageScale_s, "ElectricDamageScale");
}

}  // namespace uking::ai

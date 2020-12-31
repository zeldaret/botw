#include "Game/AI/AI/aiEquipStand.h"

namespace uking::ai {

EquipStand::EquipStand(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EquipStand::~EquipStand() = default;

bool EquipStand::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EquipStand::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EquipStand::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EquipStand::loadParams_() {
    getStaticParam(&mDisplayAttKey_s, "DisplayAttKey");
    getStaticParam(&mTakeOutAttKey_s, "TakeOutAttKey");
    getMapUnitParam(&mEquipStandSlot_m, "EquipStandSlot");
    getAITreeVariable(&mEquipDisplayChild_a, "EquipDisplayChild");
}

}  // namespace uking::ai

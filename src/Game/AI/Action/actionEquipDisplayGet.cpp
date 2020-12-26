#include "Game/AI/Action/actionEquipDisplayGet.h"

namespace uking::action {

EquipDisplayGet::EquipDisplayGet(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EquipDisplayGet::~EquipDisplayGet() = default;

bool EquipDisplayGet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EquipDisplayGet::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EquipDisplayGet::leave_() {
    ksys::act::ai::Action::leave_();
}

void EquipDisplayGet::loadParams_() {
    getMapUnitParam(&mEquipStandSlot_m, "EquipStandSlot");
    getAITreeVariable(&mEquipDisplayChild_a, "EquipDisplayChild");
}

void EquipDisplayGet::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

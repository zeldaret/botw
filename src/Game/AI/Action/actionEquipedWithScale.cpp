#include "Game/AI/Action/actionEquipedWithScale.h"

namespace uking::action {

EquipedWithScale::EquipedWithScale(const InitArg& arg) : EquipedAction(arg) {}

EquipedWithScale::~EquipedWithScale() = default;

bool EquipedWithScale::init_(sead::Heap* heap) {
    return EquipedAction::init_(heap);
}

void EquipedWithScale::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
}

void EquipedWithScale::leave_() {
    EquipedAction::leave_();
}

void EquipedWithScale::loadParams_() {
    getDynamicParam(&mNodeName_d, "NodeName");
    getDynamicParam(&mRotOffset_d, "RotOffset");
    getDynamicParam(&mTransOffset_d, "TransOffset");
}

void EquipedWithScale::calc_() {
    EquipedAction::calc_();
}

}  // namespace uking::action

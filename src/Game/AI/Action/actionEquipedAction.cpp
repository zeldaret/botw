#include "Game/AI/Action/actionEquipedAction.h"

namespace uking::action {

EquipedAction::EquipedAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EquipedAction::~EquipedAction() = default;

void EquipedAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EquipedAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EquipedAction::loadParams_() {
    getDynamicParam(&mNodeName_d, "NodeName");
    getDynamicParam(&mRotOffset_d, "RotOffset");
    getDynamicParam(&mTransOffset_d, "TransOffset");
}

void EquipedAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

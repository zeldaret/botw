#include "Game/AI/Action/actionEquipedWithScale.h"

namespace uking::action {

EquipedWithScale::EquipedWithScale(const InitArg& arg) : EquipedAction(arg) {}

EquipedWithScale::~EquipedWithScale() = default;

void EquipedWithScale::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
}

}  // namespace uking::action

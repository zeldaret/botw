#include "Game/AI/Action/actionGroupDisallowEmitAction.h"

namespace uking::action {

GroupDisallowEmitAction::GroupDisallowEmitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GroupDisallowEmitAction::~GroupDisallowEmitAction() = default;

bool GroupDisallowEmitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GroupDisallowEmitAction::loadParams_() {
    getDynamicParam(&mGroupName_d, "GroupName");
}

}  // namespace uking::action

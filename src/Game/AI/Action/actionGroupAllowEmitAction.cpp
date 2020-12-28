#include "Game/AI/Action/actionGroupAllowEmitAction.h"

namespace uking::action {

GroupAllowEmitAction::GroupAllowEmitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GroupAllowEmitAction::~GroupAllowEmitAction() = default;

bool GroupAllowEmitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GroupAllowEmitAction::loadParams_() {
    getDynamicParam(&mGroupName_d, "GroupName");
}

}  // namespace uking::action

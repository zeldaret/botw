#include "Game/AI/Action/actionGroupAllowEmitAction.h"

namespace uking::action {

GroupAllowEmitAction::GroupAllowEmitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GroupAllowEmitAction::~GroupAllowEmitAction() = default;

bool GroupAllowEmitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GroupAllowEmitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GroupAllowEmitAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void GroupAllowEmitAction::loadParams_() {
    getDynamicParam(&mGroupName_d, "GroupName");
}

void GroupAllowEmitAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

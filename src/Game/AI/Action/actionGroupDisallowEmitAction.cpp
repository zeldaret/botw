#include "Game/AI/Action/actionGroupDisallowEmitAction.h"

namespace uking::action {

GroupDisallowEmitAction::GroupDisallowEmitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GroupDisallowEmitAction::~GroupDisallowEmitAction() = default;

bool GroupDisallowEmitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GroupDisallowEmitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GroupDisallowEmitAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void GroupDisallowEmitAction::loadParams_() {
    getDynamicParam(&mGroupName_d, "GroupName");
}

void GroupDisallowEmitAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

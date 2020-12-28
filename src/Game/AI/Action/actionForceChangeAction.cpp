#include "Game/AI/Action/actionForceChangeAction.h"

namespace uking::action {

ForceChangeAction::ForceChangeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceChangeAction::~ForceChangeAction() = default;

void ForceChangeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceChangeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceChangeAction::loadParams_() {
    getStaticParam(&mTree_s, "Tree");
}

void ForceChangeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

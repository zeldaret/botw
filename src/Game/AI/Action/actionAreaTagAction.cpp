#include "Game/AI/Action/actionAreaTagAction.h"

namespace uking::action {

AreaTagAction::AreaTagAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaTagAction::~AreaTagAction() = default;

void AreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AreaTagAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionAreaTagAction.h"

namespace uking::action {

AreaTagAction::AreaTagAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaTagAction::~AreaTagAction() = default;

bool AreaTagAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AreaTagAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void AreaTagAction::loadParams_() {}

void AreaTagAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

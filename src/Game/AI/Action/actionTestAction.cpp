#include "Game/AI/Action/actionTestAction.h"

namespace uking::action {

TestAction::TestAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TestAction::~TestAction() = default;

bool TestAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TestAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TestAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void TestAction::loadParams_() {
    getDynamicParam(&mFlag_d, "Flag");
    getDynamicParam(&mName_d, "Name");
}

void TestAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

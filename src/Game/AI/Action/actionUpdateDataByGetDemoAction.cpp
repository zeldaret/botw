#include "Game/AI/Action/actionUpdateDataByGetDemoAction.h"

namespace uking::action {

UpdateDataByGetDemoAction::UpdateDataByGetDemoAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

UpdateDataByGetDemoAction::~UpdateDataByGetDemoAction() = default;

bool UpdateDataByGetDemoAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void UpdateDataByGetDemoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void UpdateDataByGetDemoAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void UpdateDataByGetDemoAction::loadParams_() {}

void UpdateDataByGetDemoAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

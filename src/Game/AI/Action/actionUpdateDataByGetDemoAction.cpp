#include "Game/AI/Action/actionUpdateDataByGetDemoAction.h"

namespace uking::action {

UpdateDataByGetDemoAction::UpdateDataByGetDemoAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

UpdateDataByGetDemoAction::~UpdateDataByGetDemoAction() = default;

bool UpdateDataByGetDemoAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void UpdateDataByGetDemoAction::loadParams_() {}

}  // namespace uking::action

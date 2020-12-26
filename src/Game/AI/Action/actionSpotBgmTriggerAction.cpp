#include "Game/AI/Action/actionSpotBgmTriggerAction.h"

namespace uking::action {

SpotBgmTriggerAction::SpotBgmTriggerAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SpotBgmTriggerAction::~SpotBgmTriggerAction() = default;

bool SpotBgmTriggerAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SpotBgmTriggerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SpotBgmTriggerAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SpotBgmTriggerAction::loadParams_() {
    getDynamicParam(&mSound_d, "Sound");
    getMapUnitParam(&mIsStopWithoutReductionY_m, "IsStopWithoutReductionY");
    getMapUnitParam(&mSound_m, "Sound");
}

void SpotBgmTriggerAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

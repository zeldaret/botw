#include "Game/AI/Action/actionFrontierSpotBgmTriggerAction.h"

namespace uking::action {

FrontierSpotBgmTriggerAction::FrontierSpotBgmTriggerAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

FrontierSpotBgmTriggerAction::~FrontierSpotBgmTriggerAction() = default;

bool FrontierSpotBgmTriggerAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FrontierSpotBgmTriggerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FrontierSpotBgmTriggerAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void FrontierSpotBgmTriggerAction::loadParams_() {
    getDynamicParam(&mSound_d, "Sound");
    getMapUnitParam(&mSpotBgmLifeScaleMargin_m, "SpotBgmLifeScaleMargin");
    getMapUnitParam(&mIsStopWithoutReductionY_m, "IsStopWithoutReductionY");
    getMapUnitParam(&mSound_m, "Sound");
    getMapUnitParam(&mShape_m, "Shape");
}

void FrontierSpotBgmTriggerAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

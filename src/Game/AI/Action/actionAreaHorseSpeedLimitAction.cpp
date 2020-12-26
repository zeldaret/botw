#include "Game/AI/Action/actionAreaHorseSpeedLimitAction.h"

namespace uking::action {

AreaHorseSpeedLimitAction::AreaHorseSpeedLimitAction(const InitArg& arg) : AreaTagAction(arg) {}

AreaHorseSpeedLimitAction::~AreaHorseSpeedLimitAction() = default;

bool AreaHorseSpeedLimitAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void AreaHorseSpeedLimitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void AreaHorseSpeedLimitAction::leave_() {
    AreaTagAction::leave_();
}

void AreaHorseSpeedLimitAction::loadParams_() {}

void AreaHorseSpeedLimitAction::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionAirWallAction.h"

namespace uking::action {

AirWallAction::AirWallAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirWallAction::~AirWallAction() = default;

bool AirWallAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirWallAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AirWallAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirWallAction::loadParams_() {}

void AirWallAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

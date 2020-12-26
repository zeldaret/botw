#include "Game/AI/Action/actionAirWallHorse.h"

namespace uking::action {

AirWallHorse::AirWallHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirWallHorse::~AirWallHorse() = default;

bool AirWallHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirWallHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AirWallHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirWallHorse::loadParams_() {}

void AirWallHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

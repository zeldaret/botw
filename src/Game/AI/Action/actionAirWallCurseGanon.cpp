#include "Game/AI/Action/actionAirWallCurseGanon.h"

namespace uking::action {

AirWallCurseGanon::AirWallCurseGanon(const InitArg& arg) : AirWallHorse(arg) {}

AirWallCurseGanon::~AirWallCurseGanon() = default;

bool AirWallCurseGanon::init_(sead::Heap* heap) {
    return AirWallHorse::init_(heap);
}

void AirWallCurseGanon::enter_(ksys::act::ai::InlineParamPack* params) {
    AirWallHorse::enter_(params);
}

void AirWallCurseGanon::leave_() {
    AirWallHorse::leave_();
}

void AirWallCurseGanon::loadParams_() {
    AirWallHorse::loadParams_();
}

void AirWallCurseGanon::calc_() {
    AirWallHorse::calc_();
}

}  // namespace uking::action

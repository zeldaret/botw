#include "Game/AI/Action/actionAirOctaMgr.h"

namespace uking::action {

AirOctaMgr::AirOctaMgr(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaMgr::~AirOctaMgr() = default;

bool AirOctaMgr::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaMgr::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AirOctaMgr::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirOctaMgr::loadParams_() {
    getStaticParam(&mLeaveDistance_s, "LeaveDistance");
    getStaticParam(&mLeaveDownY_s, "LeaveDownY");
    getStaticParam(&monGraundEscapeDist_s, "onGraundEscapeDist");
    getStaticParam(&mPlayerLostTime_s, "PlayerLostTime");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
    getMapUnitParam(&mReactHorn_m, "ReactHorn");
}

void AirOctaMgr::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

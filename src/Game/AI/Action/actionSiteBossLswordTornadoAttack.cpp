#include "Game/AI/Action/actionSiteBossLswordTornadoAttack.h"

namespace uking::action {

SiteBossLswordTornadoAttack::SiteBossLswordTornadoAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordTornadoAttack::~SiteBossLswordTornadoAttack() = default;

bool SiteBossLswordTornadoAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordTornadoAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossLswordTornadoAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordTornadoAttack::loadParams_() {
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mVacuumAcc_s, "VacuumAcc");
    getStaticParam(&mVacuumMaxSpeed_s, "VacuumMaxSpeed");
    getStaticParam(&mVacuumAngle_s, "VacuumAngle");
    getStaticParam(&mVacuumBaseWeight_s, "VacuumBaseWeight");
}

void SiteBossLswordTornadoAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

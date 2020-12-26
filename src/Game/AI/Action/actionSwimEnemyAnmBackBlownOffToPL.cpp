#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOffToPL.h"

namespace uking::action {

SwimEnemyAnmBackBlownOffToPL::SwimEnemyAnmBackBlownOffToPL(const InitArg& arg)
    : SwimEnemyAnmBackBlownOff(arg) {}

SwimEnemyAnmBackBlownOffToPL::~SwimEnemyAnmBackBlownOffToPL() = default;

bool SwimEnemyAnmBackBlownOffToPL::init_(sead::Heap* heap) {
    return SwimEnemyAnmBackBlownOff::init_(heap);
}

void SwimEnemyAnmBackBlownOffToPL::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimEnemyAnmBackBlownOff::enter_(params);
}

void SwimEnemyAnmBackBlownOffToPL::leave_() {
    SwimEnemyAnmBackBlownOff::leave_();
}

void SwimEnemyAnmBackBlownOffToPL::loadParams_() {
    SwimEnemyAnmBackBlownOff::loadParams_();
}

void SwimEnemyAnmBackBlownOffToPL::calc_() {
    SwimEnemyAnmBackBlownOff::calc_();
}

}  // namespace uking::action

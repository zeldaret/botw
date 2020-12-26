#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOffFromPL.h"

namespace uking::action {

SwimEnemyAnmBackBlownOffFromPL::SwimEnemyAnmBackBlownOffFromPL(const InitArg& arg)
    : SwimEnemyAnmBackBlownOff(arg) {}

SwimEnemyAnmBackBlownOffFromPL::~SwimEnemyAnmBackBlownOffFromPL() = default;

bool SwimEnemyAnmBackBlownOffFromPL::init_(sead::Heap* heap) {
    return SwimEnemyAnmBackBlownOff::init_(heap);
}

void SwimEnemyAnmBackBlownOffFromPL::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimEnemyAnmBackBlownOff::enter_(params);
}

void SwimEnemyAnmBackBlownOffFromPL::leave_() {
    SwimEnemyAnmBackBlownOff::leave_();
}

void SwimEnemyAnmBackBlownOffFromPL::loadParams_() {
    SwimEnemyAnmBackBlownOff::loadParams_();
}

void SwimEnemyAnmBackBlownOffFromPL::calc_() {
    SwimEnemyAnmBackBlownOff::calc_();
}

}  // namespace uking::action

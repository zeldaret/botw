#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOff.h"

namespace uking::action {

SwimEnemyAnmBackBlownOff::SwimEnemyAnmBackBlownOff(const InitArg& arg)
    : SwimEnemyAnmBackBlownOffBase(arg) {}

SwimEnemyAnmBackBlownOff::~SwimEnemyAnmBackBlownOff() = default;

bool SwimEnemyAnmBackBlownOff::init_(sead::Heap* heap) {
    return SwimEnemyAnmBackBlownOffBase::init_(heap);
}

void SwimEnemyAnmBackBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimEnemyAnmBackBlownOffBase::enter_(params);
}

void SwimEnemyAnmBackBlownOff::leave_() {
    SwimEnemyAnmBackBlownOffBase::leave_();
}

void SwimEnemyAnmBackBlownOff::loadParams_() {
    SwimEnemyAnmBackBlownOffBase::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void SwimEnemyAnmBackBlownOff::calc_() {
    SwimEnemyAnmBackBlownOffBase::calc_();
}

}  // namespace uking::action

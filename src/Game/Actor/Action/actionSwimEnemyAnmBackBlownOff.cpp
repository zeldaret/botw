#include "Game/Actor/Action/actionSwimEnemyAnmBackBlownOff.h"

namespace uking::action {

SwimEnemyAnmBackBlownOff::SwimEnemyAnmBackBlownOff(const InitArg& arg)
    : SwimEnemyBlownOffBase(arg) {}

SwimEnemyAnmBackBlownOff::~SwimEnemyAnmBackBlownOff() = default;

bool SwimEnemyAnmBackBlownOff::init_(sead::Heap* heap) {
    return SwimEnemyBlownOffBase::init_(heap);
}

void SwimEnemyAnmBackBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimEnemyBlownOffBase::enter_(params);
}

void SwimEnemyAnmBackBlownOff::leave_() {
    SwimEnemyBlownOffBase::leave_();
}

void SwimEnemyAnmBackBlownOff::loadParams_() {
    SwimEnemyBlownOffBase::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void SwimEnemyAnmBackBlownOff::calc_() {
    SwimEnemyBlownOffBase::calc_();
}

}  // namespace uking::action

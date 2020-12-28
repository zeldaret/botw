#include "Game/AI/Action/actionPriestBossBlownOff.h"

namespace uking::action {

PriestBossBlownOff::PriestBossBlownOff(const InitArg& arg) : BlownOff(arg) {}

PriestBossBlownOff::~PriestBossBlownOff() = default;

void PriestBossBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
}

void PriestBossBlownOff::leave_() {
    BlownOff::leave_();
}

void PriestBossBlownOff::loadParams_() {
    BlownOff::loadParams_();
}

void PriestBossBlownOff::calc_() {
    BlownOff::calc_();
}

}  // namespace uking::action

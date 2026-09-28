#include "Game/Actor/Action/actionLastBossBlowOff.h"

namespace uking::action {

LastBossBlowOff::LastBossBlowOff(const InitArg& arg) : BlownOff(arg) {}

LastBossBlowOff::~LastBossBlowOff() = default;

bool LastBossBlowOff::init_(sead::Heap* heap) {
    return BlownOff::init_(heap);
}

void LastBossBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
}

void LastBossBlowOff::leave_() {
    BlownOff::leave_();
}

void LastBossBlowOff::loadParams_() {
    BlownOff::loadParams_();
}

void LastBossBlowOff::calc_() {
    BlownOff::calc_();
}

}  // namespace uking::action

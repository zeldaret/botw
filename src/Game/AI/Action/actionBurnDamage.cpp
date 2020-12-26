#include "Game/AI/Action/actionBurnDamage.h"

namespace uking::action {

BurnDamage::BurnDamage(const InitArg& arg) : TimeredASPlay(arg) {}

BurnDamage::~BurnDamage() = default;

bool BurnDamage::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap);
}

void BurnDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
}

void BurnDamage::leave_() {
    TimeredASPlay::leave_();
}

void BurnDamage::loadParams_() {
    TimeredASPlay::loadParams_();
}

void BurnDamage::calc_() {
    TimeredASPlay::calc_();
}

}  // namespace uking::action

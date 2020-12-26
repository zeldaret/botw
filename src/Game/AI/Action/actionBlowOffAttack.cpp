#include "Game/AI/Action/actionBlowOffAttack.h"

namespace uking::action {

BlowOffAttack::BlowOffAttack(const InitArg& arg) : Attack(arg) {}

BlowOffAttack::~BlowOffAttack() = default;

bool BlowOffAttack::init_(sead::Heap* heap) {
    return Attack::init_(heap);
}

void BlowOffAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    Attack::enter_(params);
}

void BlowOffAttack::leave_() {
    Attack::leave_();
}

void BlowOffAttack::loadParams_() {
    Attack::loadParams_();
}

void BlowOffAttack::calc_() {
    Attack::calc_();
}

}  // namespace uking::action

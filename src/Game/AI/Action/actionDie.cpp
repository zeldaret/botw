#include "Game/AI/Action/actionDie.h"

namespace uking::action {

Die::Die(const InitArg& arg) : BlownOff(arg) {}

Die::~Die() = default;

bool Die::init_(sead::Heap* heap) {
    return BlownOff::init_(heap);
}

void Die::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
}

void Die::leave_() {
    BlownOff::leave_();
}

void Die::loadParams_() {
    BlownOff::loadParams_();
}

void Die::calc_() {
    BlownOff::calc_();
}

}  // namespace uking::action

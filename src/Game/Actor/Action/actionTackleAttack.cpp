#include "Game/Actor/Action/actionTackleAttack.h"

namespace uking::action {

TackleAttack::TackleAttack(const InitArg& arg) : TackleMove(arg) {}

TackleAttack::~TackleAttack() = default;

bool TackleAttack::init_(sead::Heap* heap) {
    return TackleMove::init_(heap);
}

void TackleAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    TackleMove::enter_(params);
}

void TackleAttack::leave_() {
    TackleMove::leave_();
}

void TackleAttack::loadParams_() {
    TackleMove::loadParams_();
    getStaticParam(&mAtkSensorName_s, "AtkSensorName");
}

void TackleAttack::calc_() {
    TackleMove::calc_();
}

}  // namespace uking::action

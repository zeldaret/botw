#include "Game/AI/Action/actionTowingBrake.h"

namespace uking::action {

TowingBrake::TowingBrake(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TowingBrake::~TowingBrake() = default;

bool TowingBrake::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TowingBrake::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TowingBrake::leave_() {
    ksys::act::ai::Action::leave_();
}

void TowingBrake::loadParams_() {}

void TowingBrake::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

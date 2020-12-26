#include "Game/AI/Action/actionSweepCollision.h"

namespace uking::action {

SweepCollision::SweepCollision(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SweepCollision::~SweepCollision() = default;

bool SweepCollision::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SweepCollision::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SweepCollision::leave_() {
    ksys::act::ai::Action::leave_();
}

void SweepCollision::loadParams_() {}

void SweepCollision::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

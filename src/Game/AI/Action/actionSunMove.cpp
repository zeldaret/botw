#include "Game/AI/Action/actionSunMove.h"

namespace uking::action {

SunMove::SunMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SunMove::~SunMove() = default;

bool SunMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SunMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SunMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void SunMove::loadParams_() {}

void SunMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

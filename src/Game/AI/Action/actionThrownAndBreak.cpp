#include "Game/AI/Action/actionThrownAndBreak.h"

namespace uking::action {

ThrownAndBreak::ThrownAndBreak(const InitArg& arg) : Thrown(arg) {}

ThrownAndBreak::~ThrownAndBreak() = default;

bool ThrownAndBreak::init_(sead::Heap* heap) {
    return Thrown::init_(heap);
}

void ThrownAndBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    Thrown::enter_(params);
}

void ThrownAndBreak::leave_() {
    Thrown::leave_();
}

void ThrownAndBreak::loadParams_() {
    Thrown::loadParams_();
}

void ThrownAndBreak::calc_() {
    Thrown::calc_();
}

}  // namespace uking::action

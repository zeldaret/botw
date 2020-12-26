#include "Game/AI/Action/actionIsMorphEndASPlay.h"

namespace uking::action {

IsMorphEndASPlay::IsMorphEndASPlay(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IsMorphEndASPlay::~IsMorphEndASPlay() = default;

bool IsMorphEndASPlay::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void IsMorphEndASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void IsMorphEndASPlay::leave_() {
    OnetimeStopASPlay::leave_();
}

void IsMorphEndASPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
}

void IsMorphEndASPlay::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action

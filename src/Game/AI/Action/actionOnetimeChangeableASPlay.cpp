#include "Game/AI/Action/actionOnetimeChangeableASPlay.h"

namespace uking::action {

OnetimeChangeableASPlay::OnetimeChangeableASPlay(const InitArg& arg) : OnetimeStopASPlay(arg) {}

OnetimeChangeableASPlay::~OnetimeChangeableASPlay() = default;

bool OnetimeChangeableASPlay::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void OnetimeChangeableASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void OnetimeChangeableASPlay::leave_() {
    OnetimeStopASPlay::leave_();
}

void OnetimeChangeableASPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
}

void OnetimeChangeableASPlay::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action

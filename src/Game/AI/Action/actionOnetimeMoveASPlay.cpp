#include "Game/AI/Action/actionOnetimeMoveASPlay.h"

namespace uking::action {

OnetimeMoveASPlay::OnetimeMoveASPlay(const InitArg& arg) : OnetimeStopASPlay(arg) {}

OnetimeMoveASPlay::~OnetimeMoveASPlay() = default;

bool OnetimeMoveASPlay::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void OnetimeMoveASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void OnetimeMoveASPlay::leave_() {
    OnetimeStopASPlay::leave_();
}

void OnetimeMoveASPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIsChangable_s, "IsChangable");
}

void OnetimeMoveASPlay::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action

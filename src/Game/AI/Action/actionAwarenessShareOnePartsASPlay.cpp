#include "Game/AI/Action/actionAwarenessShareOnePartsASPlay.h"

namespace uking::action {

AwarenessShareOnePartsASPlay::AwarenessShareOnePartsASPlay(const InitArg& arg)
    : OnetimeStopASPlay(arg) {}

AwarenessShareOnePartsASPlay::~AwarenessShareOnePartsASPlay() = default;

bool AwarenessShareOnePartsASPlay::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void AwarenessShareOnePartsASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void AwarenessShareOnePartsASPlay::leave_() {
    OnetimeStopASPlay::leave_();
}

void AwarenessShareOnePartsASPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mPartsKey_s, "PartsKey");
}

void AwarenessShareOnePartsASPlay::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action

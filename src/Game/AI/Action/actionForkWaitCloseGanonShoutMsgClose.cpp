#include "Game/AI/Action/actionForkWaitCloseGanonShoutMsgClose.h"

namespace uking::action {

ForkWaitCloseGanonShoutMsgClose::ForkWaitCloseGanonShoutMsgClose(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkWaitCloseGanonShoutMsgClose::~ForkWaitCloseGanonShoutMsgClose() = default;

bool ForkWaitCloseGanonShoutMsgClose::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkWaitCloseGanonShoutMsgClose::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkWaitCloseGanonShoutMsgClose::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkWaitCloseGanonShoutMsgClose::loadParams_() {
    getAITreeVariable(&mInBeastGanonVoiceSequence_a, "InBeastGanonVoiceSequence");
}

void ForkWaitCloseGanonShoutMsgClose::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

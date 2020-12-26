#include "Game/AI/Action/actionBecomeSpeaker.h"

namespace uking::action {

BecomeSpeaker::BecomeSpeaker(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BecomeSpeaker::~BecomeSpeaker() = default;

bool BecomeSpeaker::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BecomeSpeaker::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BecomeSpeaker::leave_() {
    ksys::act::ai::Action::leave_();
}

void BecomeSpeaker::loadParams_() {}

void BecomeSpeaker::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

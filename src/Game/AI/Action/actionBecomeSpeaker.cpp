#include "Game/AI/Action/actionBecomeSpeaker.h"

namespace uking::action {

BecomeSpeaker::BecomeSpeaker(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BecomeSpeaker::~BecomeSpeaker() = default;

bool BecomeSpeaker::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BecomeSpeaker::loadParams_() {}

}  // namespace uking::action

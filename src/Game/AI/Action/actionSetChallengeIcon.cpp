#include "Game/AI/Action/actionSetChallengeIcon.h"

namespace uking::action {

SetChallengeIcon::SetChallengeIcon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetChallengeIcon::~SetChallengeIcon() = default;

bool SetChallengeIcon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetChallengeIcon::loadParams_() {
    getDynamicParam(&mChallengeName_d, "ChallengeName");
}

}  // namespace uking::action

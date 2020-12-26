#include "Game/AI/Action/actionSetChallengeIcon.h"

namespace uking::action {

SetChallengeIcon::SetChallengeIcon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetChallengeIcon::~SetChallengeIcon() = default;

bool SetChallengeIcon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetChallengeIcon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetChallengeIcon::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetChallengeIcon::loadParams_() {
    getDynamicParam(&mChallengeName_d, "ChallengeName");
}

void SetChallengeIcon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

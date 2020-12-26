#include "Game/AI/Action/actionSetActorNameToGameDataString.h"

namespace uking::action {

SetActorNameToGameDataString::SetActorNameToGameDataString(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetActorNameToGameDataString::~SetActorNameToGameDataString() = default;

bool SetActorNameToGameDataString::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetActorNameToGameDataString::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetActorNameToGameDataString::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetActorNameToGameDataString::loadParams_() {
    getDynamicParam(&mGameDataStringName_d, "GameDataStringName");
    getDynamicParam(&mActorName_d, "ActorName");
}

void SetActorNameToGameDataString::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionSetActorNameToGameDataString.h"

namespace uking::action {

SetActorNameToGameDataString::SetActorNameToGameDataString(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetActorNameToGameDataString::~SetActorNameToGameDataString() = default;

bool SetActorNameToGameDataString::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetActorNameToGameDataString::loadParams_() {
    getDynamicParam(&mGameDataStringName_d, "GameDataStringName");
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action

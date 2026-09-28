#include "Game/Actor/Action/actionSetGetFlagByActorName.h"

namespace uking::action {

SetGetFlagByActorName::SetGetFlagByActorName(const InitArg& arg) : SetFlag(arg) {}

SetGetFlagByActorName::~SetGetFlagByActorName() = default;

bool SetGetFlagByActorName::init_(sead::Heap* heap) {
    return SetFlag::init_(heap);
}

void SetGetFlagByActorName::loadParams_() {
    SetFlag::loadParams_();
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action

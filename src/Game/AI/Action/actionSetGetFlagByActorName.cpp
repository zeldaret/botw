#include "Game/AI/Action/actionSetGetFlagByActorName.h"

namespace uking::action {

SetGetFlagByActorName::SetGetFlagByActorName(const InitArg& arg) : SetGetFlagBase(arg) {}

SetGetFlagByActorName::~SetGetFlagByActorName() = default;

bool SetGetFlagByActorName::init_(sead::Heap* heap) {
    return SetGetFlagBase::init_(heap);
}

void SetGetFlagByActorName::loadParams_() {
    SetGetFlagBase::loadParams_();
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action

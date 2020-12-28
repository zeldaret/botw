#include "Game/AI/Action/actionSetGetFlag.h"

namespace uking::action {

SetGetFlag::SetGetFlag(const InitArg& arg) : SetGetFlagBase(arg) {}

SetGetFlag::~SetGetFlag() = default;

bool SetGetFlag::init_(sead::Heap* heap) {
    return SetGetFlagBase::init_(heap);
}

void SetGetFlag::loadParams_() {
    SetGetFlagBase::loadParams_();
}

}  // namespace uking::action

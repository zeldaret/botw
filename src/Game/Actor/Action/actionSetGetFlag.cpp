#include "Game/Actor/Action/actionSetGetFlag.h"

namespace uking::action {

SetGetFlag::SetGetFlag(const InitArg& arg) : SetFlag(arg) {}

SetGetFlag::~SetGetFlag() = default;

bool SetGetFlag::init_(sead::Heap* heap) {
    return SetFlag::init_(heap);
}

void SetGetFlag::loadParams_() {
    SetFlag::loadParams_();
}

}  // namespace uking::action

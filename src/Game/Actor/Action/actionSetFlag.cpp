#include "Game/Actor/Action/actionSetFlag.h"

namespace uking::action {

SetFlag::SetFlag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetFlag::~SetFlag() = default;

bool SetFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetFlag::loadParams_() {}

}  // namespace uking::action

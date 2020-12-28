#include "Game/AI/Action/actionSetCurrentDungeonClearFlag.h"

namespace uking::action {

SetCurrentDungeonClearFlag::SetCurrentDungeonClearFlag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetCurrentDungeonClearFlag::~SetCurrentDungeonClearFlag() = default;

bool SetCurrentDungeonClearFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetCurrentDungeonClearFlag::loadParams_() {}

}  // namespace uking::action

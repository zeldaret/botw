#include "Game/AI/Action/actionSetEnterDungeonFlag.h"

namespace uking::action {

SetEnterDungeonFlag::SetEnterDungeonFlag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetEnterDungeonFlag::~SetEnterDungeonFlag() = default;

bool SetEnterDungeonFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetEnterDungeonFlag::loadParams_() {}

}  // namespace uking::action

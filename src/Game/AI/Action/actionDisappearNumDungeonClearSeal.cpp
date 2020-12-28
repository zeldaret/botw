#include "Game/AI/Action/actionDisappearNumDungeonClearSeal.h"

namespace uking::action {

DisappearNumDungeonClearSeal::DisappearNumDungeonClearSeal(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DisappearNumDungeonClearSeal::~DisappearNumDungeonClearSeal() = default;

bool DisappearNumDungeonClearSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisappearNumDungeonClearSeal::loadParams_() {}

}  // namespace uking::action

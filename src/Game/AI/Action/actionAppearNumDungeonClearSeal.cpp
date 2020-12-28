#include "Game/AI/Action/actionAppearNumDungeonClearSeal.h"

namespace uking::action {

AppearNumDungeonClearSeal::AppearNumDungeonClearSeal(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AppearNumDungeonClearSeal::~AppearNumDungeonClearSeal() = default;

bool AppearNumDungeonClearSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearNumDungeonClearSeal::loadParams_() {}

}  // namespace uking::action

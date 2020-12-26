#include "Game/AI/Action/actionSetCurrentDungeonClearFlag.h"

namespace uking::action {

SetCurrentDungeonClearFlag::SetCurrentDungeonClearFlag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SetCurrentDungeonClearFlag::~SetCurrentDungeonClearFlag() = default;

bool SetCurrentDungeonClearFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetCurrentDungeonClearFlag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetCurrentDungeonClearFlag::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetCurrentDungeonClearFlag::loadParams_() {}

void SetCurrentDungeonClearFlag::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

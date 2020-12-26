#include "Game/AI/Action/actionSetEnterDungeonFlag.h"

namespace uking::action {

SetEnterDungeonFlag::SetEnterDungeonFlag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetEnterDungeonFlag::~SetEnterDungeonFlag() = default;

bool SetEnterDungeonFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetEnterDungeonFlag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetEnterDungeonFlag::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetEnterDungeonFlag::loadParams_() {}

void SetEnterDungeonFlag::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

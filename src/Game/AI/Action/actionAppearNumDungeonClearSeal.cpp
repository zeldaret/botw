#include "Game/AI/Action/actionAppearNumDungeonClearSeal.h"

namespace uking::action {

AppearNumDungeonClearSeal::AppearNumDungeonClearSeal(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AppearNumDungeonClearSeal::~AppearNumDungeonClearSeal() = default;

bool AppearNumDungeonClearSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearNumDungeonClearSeal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AppearNumDungeonClearSeal::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearNumDungeonClearSeal::loadParams_() {}

void AppearNumDungeonClearSeal::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

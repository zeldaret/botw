#include "Game/AI/Action/actionIncreaseNumDungeonClearSeal.h"

namespace uking::action {

IncreaseNumDungeonClearSeal::IncreaseNumDungeonClearSeal(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

IncreaseNumDungeonClearSeal::~IncreaseNumDungeonClearSeal() = default;

bool IncreaseNumDungeonClearSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IncreaseNumDungeonClearSeal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IncreaseNumDungeonClearSeal::leave_() {
    ksys::act::ai::Action::leave_();
}

void IncreaseNumDungeonClearSeal::loadParams_() {
    getStaticParam(&mActorName_s, "ActorName");
    getDynamicParam(&mValue_d, "Value");
}

void IncreaseNumDungeonClearSeal::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

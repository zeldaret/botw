#include "Game/AI/Action/actionHorseWaitForEventAction.h"

namespace uking::action {

HorseWaitForEventAction::HorseWaitForEventAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseWaitForEventAction::~HorseWaitForEventAction() = default;

bool HorseWaitForEventAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseWaitForEventAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseWaitForEventAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseWaitForEventAction::loadParams_() {
    getDynamicParam(&mIsAngryEnable_d, "IsAngryEnable");
    getDynamicParam(&mIsEatEnable_d, "IsEatEnable");
    getDynamicParam(&mIsLoveEnable_d, "IsLoveEnable");
    getDynamicParam(&mHasToCue_d, "HasToCue");
    getDynamicParam(&mIsNoMorph_d, "IsNoMorph");
}

void HorseWaitForEventAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

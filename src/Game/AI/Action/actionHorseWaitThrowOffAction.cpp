#include "Game/AI/Action/actionHorseWaitThrowOffAction.h"

namespace uking::action {

HorseWaitThrowOffAction::HorseWaitThrowOffAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseWaitThrowOffAction::~HorseWaitThrowOffAction() = default;

bool HorseWaitThrowOffAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseWaitThrowOffAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseWaitThrowOffAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseWaitThrowOffAction::loadParams_() {
    getStaticParam(&mSucceedGear_s, "SucceedGear");
    getStaticParam(&mSetRideAttentionInvalid_s, "SetRideAttentionInvalid");
}

void HorseWaitThrowOffAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

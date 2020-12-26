#include "Game/AI/Action/actionHorseWaitEx.h"

namespace uking::action {

HorseWaitEx::HorseWaitEx(const InitArg& arg) : HorseWaitAction(arg) {}

HorseWaitEx::~HorseWaitEx() = default;

bool HorseWaitEx::init_(sead::Heap* heap) {
    return HorseWaitAction::init_(heap);
}

void HorseWaitEx::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseWaitAction::enter_(params);
}

void HorseWaitEx::leave_() {
    HorseWaitAction::leave_();
}

void HorseWaitEx::loadParams_() {
    HorseWaitAction::loadParams_();
    getStaticParam(&mKeepFrame_s, "KeepFrame");
}

void HorseWaitEx::calc_() {
    HorseWaitAction::calc_();
}

}  // namespace uking::action

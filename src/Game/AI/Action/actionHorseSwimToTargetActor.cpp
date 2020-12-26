#include "Game/AI/Action/actionHorseSwimToTargetActor.h"

namespace uking::action {

HorseSwimToTargetActor::HorseSwimToTargetActor(const InitArg& arg) : HorseSwim(arg) {}

HorseSwimToTargetActor::~HorseSwimToTargetActor() = default;

bool HorseSwimToTargetActor::init_(sead::Heap* heap) {
    return HorseSwim::init_(heap);
}

void HorseSwimToTargetActor::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseSwim::enter_(params);
}

void HorseSwimToTargetActor::leave_() {
    HorseSwim::leave_();
}

void HorseSwimToTargetActor::loadParams_() {
    HorseSwim::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseSwimToTargetActor::calc_() {
    HorseSwim::calc_();
}

}  // namespace uking::action

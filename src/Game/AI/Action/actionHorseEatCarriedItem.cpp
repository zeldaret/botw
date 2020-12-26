#include "Game/AI/Action/actionHorseEatCarriedItem.h"

namespace uking::action {

HorseEatCarriedItem::HorseEatCarriedItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseEatCarriedItem::~HorseEatCarriedItem() = default;

bool HorseEatCarriedItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseEatCarriedItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseEatCarriedItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseEatCarriedItem::loadParams_() {
    getStaticParam(&mThresholdForEat_s, "ThresholdForEat");
    getStaticParam(&mCarriedItemPosRTYOffset_s, "CarriedItemPosRTYOffset");
    getStaticParam(&mCarriedItemPosRTYWidth_s, "CarriedItemPosRTYWidth");
    getStaticParam(&mDelayFrames_s, "DelayFrames");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseEatCarriedItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

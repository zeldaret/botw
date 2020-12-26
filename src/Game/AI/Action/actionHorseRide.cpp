#include "Game/AI/Action/actionHorseRide.h"

namespace uking::action {

HorseRide::HorseRide(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseRide::~HorseRide() = default;

bool HorseRide::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseRide::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseRide::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
}

void HorseRide::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

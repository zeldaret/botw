#include "Game/Actor/Action/actionHorseRideBase.h"

namespace uking::action {

HorseRideBase::HorseRideBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseRideBase::~HorseRideBase() = default;

bool HorseRideBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseRideBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseRideBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseRideBase::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
}

void HorseRideBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionRisingAirOneTime.h"

namespace uking::action {

RisingAirOneTime::RisingAirOneTime(const InitArg& arg) : AscendingCurrent(arg) {}

RisingAirOneTime::~RisingAirOneTime() = default;

bool RisingAirOneTime::init_(sead::Heap* heap) {
    return AscendingCurrent::init_(heap);
}

void RisingAirOneTime::enter_(ksys::act::ai::InlineParamPack* params) {
    AscendingCurrent::enter_(params);
}

void RisingAirOneTime::leave_() {
    AscendingCurrent::leave_();
}

void RisingAirOneTime::loadParams_() {
    AscendingCurrent::loadParams_();
    getStaticParam(&mLostCounter_s, "LostCounter");
}

void RisingAirOneTime::calc_() {
    AscendingCurrent::calc_();
}

}  // namespace uking::action

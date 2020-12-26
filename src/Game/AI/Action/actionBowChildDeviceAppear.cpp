#include "Game/AI/Action/actionBowChildDeviceAppear.h"

namespace uking::action {

BowChildDeviceAppear::BowChildDeviceAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildDeviceAppear::~BowChildDeviceAppear() = default;

bool BowChildDeviceAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildDeviceAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BowChildDeviceAppear::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildDeviceAppear::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mEndTime_s, "EndTime");
}

void BowChildDeviceAppear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

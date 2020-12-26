#include "Game/AI/Action/actionSubAnmBlownOff.h"

namespace uking::action {

SubAnmBlownOff::SubAnmBlownOff(const InitArg& arg) : AnmBlownOff(arg) {}

SubAnmBlownOff::~SubAnmBlownOff() = default;

bool SubAnmBlownOff::init_(sead::Heap* heap) {
    return AnmBlownOff::init_(heap);
}

void SubAnmBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmBlownOff::enter_(params);
}

void SubAnmBlownOff::leave_() {
    AnmBlownOff::leave_();
}

void SubAnmBlownOff::loadParams_() {
    AnmBlownOff::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mLeaveSubAS_s, "LeaveSubAS");
}

void SubAnmBlownOff::calc_() {
    AnmBlownOff::calc_();
}

}  // namespace uking::action

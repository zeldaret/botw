#include "Game/AI/Action/actionSubAnmKnockBackShock.h"

namespace uking::action {

SubAnmKnockBackShock::SubAnmKnockBackShock(const InitArg& arg) : AnmKnockBackShock(arg) {}

SubAnmKnockBackShock::~SubAnmKnockBackShock() = default;

bool SubAnmKnockBackShock::init_(sead::Heap* heap) {
    return AnmKnockBackShock::init_(heap);
}

void SubAnmKnockBackShock::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmKnockBackShock::enter_(params);
}

void SubAnmKnockBackShock::leave_() {
    AnmKnockBackShock::leave_();
}

void SubAnmKnockBackShock::loadParams_() {
    AnmKnockBackShock::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mLeaveSubAS_s, "LeaveSubAS");
}

void SubAnmKnockBackShock::calc_() {
    AnmKnockBackShock::calc_();
}

}  // namespace uking::action

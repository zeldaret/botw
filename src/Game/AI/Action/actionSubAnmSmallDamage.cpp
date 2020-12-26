#include "Game/AI/Action/actionSubAnmSmallDamage.h"

namespace uking::action {

SubAnmSmallDamage::SubAnmSmallDamage(const InitArg& arg) : SmallDamage(arg) {}

SubAnmSmallDamage::~SubAnmSmallDamage() = default;

bool SubAnmSmallDamage::init_(sead::Heap* heap) {
    return SmallDamage::init_(heap);
}

void SubAnmSmallDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    SmallDamage::enter_(params);
}

void SubAnmSmallDamage::leave_() {
    SmallDamage::leave_();
}

void SubAnmSmallDamage::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mLeaveSubAS_s, "LeaveSubAS");
}

void SubAnmSmallDamage::calc_() {
    SmallDamage::calc_();
}

}  // namespace uking::action

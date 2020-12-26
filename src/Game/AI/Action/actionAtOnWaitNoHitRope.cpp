#include "Game/AI/Action/actionAtOnWaitNoHitRope.h"

namespace uking::action {

AtOnWaitNoHitRope::AtOnWaitNoHitRope(const InitArg& arg) : AtOnWait(arg) {}

AtOnWaitNoHitRope::~AtOnWaitNoHitRope() = default;

bool AtOnWaitNoHitRope::init_(sead::Heap* heap) {
    return AtOnWait::init_(heap);
}

void AtOnWaitNoHitRope::enter_(ksys::act::ai::InlineParamPack* params) {
    AtOnWait::enter_(params);
}

void AtOnWaitNoHitRope::leave_() {
    AtOnWait::leave_();
}

void AtOnWaitNoHitRope::loadParams_() {
    AtOnWait::loadParams_();
    getStaticParam(&mAtkAttrType_s, "AtkAttrType");
}

void AtOnWaitNoHitRope::calc_() {
    AtOnWait::calc_();
}

}  // namespace uking::action

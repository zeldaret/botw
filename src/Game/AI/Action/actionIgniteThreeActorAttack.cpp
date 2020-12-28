#include "Game/AI/Action/actionIgniteThreeActorAttack.h"

namespace uking::action {

IgniteThreeActorAttack::IgniteThreeActorAttack(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IgniteThreeActorAttack::~IgniteThreeActorAttack() = default;

void IgniteThreeActorAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void IgniteThreeActorAttack::leave_() {
    OnetimeStopASPlay::leave_();
}

void IgniteThreeActorAttack::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
    getDynamicParam(&mIgniteHandle2_d, "IgniteHandle2");
    getDynamicParam(&mIgniteHandle3_d, "IgniteHandle3");
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mBaseNode_s, "BaseNode");
}

void IgniteThreeActorAttack::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action

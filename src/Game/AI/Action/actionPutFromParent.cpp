#include "Game/AI/Action/actionPutFromParent.h"

namespace uking::action {

PutFromParent::PutFromParent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PutFromParent::~PutFromParent() = default;

void PutFromParent::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PutFromParent::leave_() {
    ksys::act::ai::Action::leave_();
}

void PutFromParent::loadParams_() {
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mHoldOffXLinkKey_s, "HoldOffXLinkKey");
}

void PutFromParent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionPutFromParent.h"

namespace uking::action {

PutFromParent::PutFromParent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PutFromParent::~PutFromParent() = default;

bool PutFromParent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

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

#include "Game/AI/Action/actionBecomePreActor.h"

namespace uking::action {

BecomePreActor::BecomePreActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BecomePreActor::~BecomePreActor() = default;

bool BecomePreActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BecomePreActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BecomePreActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void BecomePreActor::loadParams_() {}

void BecomePreActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

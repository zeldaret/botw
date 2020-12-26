#include "Game/AI/Action/actionEventSetAttentionForbidSale.h"

namespace uking::action {

EventSetAttentionForbidSale::EventSetAttentionForbidSale(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetAttentionForbidSale::~EventSetAttentionForbidSale() = default;

bool EventSetAttentionForbidSale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetAttentionForbidSale::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetAttentionForbidSale::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetAttentionForbidSale::loadParams_() {}

void EventSetAttentionForbidSale::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

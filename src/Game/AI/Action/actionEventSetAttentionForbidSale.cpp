#include "Game/AI/Action/actionEventSetAttentionForbidSale.h"

namespace uking::action {

EventSetAttentionForbidSale::EventSetAttentionForbidSale(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetAttentionForbidSale::~EventSetAttentionForbidSale() = default;

bool EventSetAttentionForbidSale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetAttentionForbidSale::loadParams_() {}

}  // namespace uking::action

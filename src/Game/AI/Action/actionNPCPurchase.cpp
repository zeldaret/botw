#include "Game/AI/Action/actionNPCPurchase.h"

namespace uking::action {

NPCPurchase::NPCPurchase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCPurchase::~NPCPurchase() = default;

bool NPCPurchase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCPurchase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCPurchase::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCPurchase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

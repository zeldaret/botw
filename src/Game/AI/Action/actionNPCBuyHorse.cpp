#include "Game/AI/Action/actionNPCBuyHorse.h"

namespace uking::action {

NPCBuyHorse::NPCBuyHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCBuyHorse::~NPCBuyHorse() = default;

bool NPCBuyHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCBuyHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCBuyHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCBuyHorse::loadParams_() {
    getAITreeVariable(&mEventBindUnit_a, "EventBindUnit");
}

void NPCBuyHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

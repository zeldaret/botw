#include "Game/AI/Action/actionNPCReceiveHorse.h"

namespace uking::action {

NPCReceiveHorse::NPCReceiveHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCReceiveHorse::~NPCReceiveHorse() = default;

bool NPCReceiveHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCReceiveHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCReceiveHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCReceiveHorse::loadParams_() {}

void NPCReceiveHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

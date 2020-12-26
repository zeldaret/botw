#include "Game/AI/Action/actionNPCRegisterAndReceiveHorse.h"

namespace uking::action {

NPCRegisterAndReceiveHorse::NPCRegisterAndReceiveHorse(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCRegisterAndReceiveHorse::~NPCRegisterAndReceiveHorse() = default;

bool NPCRegisterAndReceiveHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCRegisterAndReceiveHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCRegisterAndReceiveHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCRegisterAndReceiveHorse::loadParams_() {}

void NPCRegisterAndReceiveHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

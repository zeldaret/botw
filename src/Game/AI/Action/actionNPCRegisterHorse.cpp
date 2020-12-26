#include "Game/AI/Action/actionNPCRegisterHorse.h"

namespace uking::action {

NPCRegisterHorse::NPCRegisterHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCRegisterHorse::~NPCRegisterHorse() = default;

bool NPCRegisterHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCRegisterHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCRegisterHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCRegisterHorse::loadParams_() {}

void NPCRegisterHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

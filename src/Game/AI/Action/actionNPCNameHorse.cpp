#include "Game/AI/Action/actionNPCNameHorse.h"

namespace uking::action {

NPCNameHorse::NPCNameHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCNameHorse::~NPCNameHorse() = default;

bool NPCNameHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCNameHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCNameHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCNameHorse::loadParams_() {}

void NPCNameHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

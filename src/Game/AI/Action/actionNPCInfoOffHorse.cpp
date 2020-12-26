#include "Game/AI/Action/actionNPCInfoOffHorse.h"

namespace uking::action {

NPCInfoOffHorse::NPCInfoOffHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCInfoOffHorse::~NPCInfoOffHorse() = default;

bool NPCInfoOffHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCInfoOffHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCInfoOffHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCInfoOffHorse::loadParams_() {}

void NPCInfoOffHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

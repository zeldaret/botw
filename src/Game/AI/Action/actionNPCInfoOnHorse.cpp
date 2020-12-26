#include "Game/AI/Action/actionNPCInfoOnHorse.h"

namespace uking::action {

NPCInfoOnHorse::NPCInfoOnHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCInfoOnHorse::~NPCInfoOnHorse() = default;

bool NPCInfoOnHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCInfoOnHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCInfoOnHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCInfoOnHorse::loadParams_() {}

void NPCInfoOnHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

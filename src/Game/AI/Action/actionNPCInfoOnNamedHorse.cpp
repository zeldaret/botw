#include "Game/AI/Action/actionNPCInfoOnNamedHorse.h"

namespace uking::action {

NPCInfoOnNamedHorse::NPCInfoOnNamedHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCInfoOnNamedHorse::~NPCInfoOnNamedHorse() = default;

bool NPCInfoOnNamedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCInfoOnNamedHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCInfoOnNamedHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCInfoOnNamedHorse::loadParams_() {}

void NPCInfoOnNamedHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

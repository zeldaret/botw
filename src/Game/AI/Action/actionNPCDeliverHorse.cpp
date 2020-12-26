#include "Game/AI/Action/actionNPCDeliverHorse.h"

namespace uking::action {

NPCDeliverHorse::NPCDeliverHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDeliverHorse::~NPCDeliverHorse() = default;

bool NPCDeliverHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCDeliverHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCDeliverHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCDeliverHorse::loadParams_() {}

void NPCDeliverHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

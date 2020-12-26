#include "Game/AI/Action/actionNPCChangeBoots.h"

namespace uking::action {

NPCChangeBoots::NPCChangeBoots(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCChangeBoots::~NPCChangeBoots() = default;

bool NPCChangeBoots::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCChangeBoots::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCChangeBoots::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCChangeBoots::loadParams_() {
    getDynamicParam(&mBootsNumber_d, "BootsNumber");
}

void NPCChangeBoots::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

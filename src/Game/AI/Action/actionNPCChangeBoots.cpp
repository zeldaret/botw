#include "Game/AI/Action/actionNPCChangeBoots.h"

namespace uking::action {

NPCChangeBoots::NPCChangeBoots(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCChangeBoots::~NPCChangeBoots() = default;

bool NPCChangeBoots::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCChangeBoots::loadParams_() {
    getDynamicParam(&mBootsNumber_d, "BootsNumber");
}

}  // namespace uking::action

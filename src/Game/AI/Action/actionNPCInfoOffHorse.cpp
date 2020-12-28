#include "Game/AI/Action/actionNPCInfoOffHorse.h"

namespace uking::action {

NPCInfoOffHorse::NPCInfoOffHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCInfoOffHorse::~NPCInfoOffHorse() = default;

bool NPCInfoOffHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCInfoOffHorse::loadParams_() {}

}  // namespace uking::action

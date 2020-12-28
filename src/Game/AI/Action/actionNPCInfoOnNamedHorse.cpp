#include "Game/AI/Action/actionNPCInfoOnNamedHorse.h"

namespace uking::action {

NPCInfoOnNamedHorse::NPCInfoOnNamedHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCInfoOnNamedHorse::~NPCInfoOnNamedHorse() = default;

bool NPCInfoOnNamedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCInfoOnNamedHorse::loadParams_() {}

}  // namespace uking::action

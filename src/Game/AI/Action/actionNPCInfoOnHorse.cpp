#include "Game/AI/Action/actionNPCInfoOnHorse.h"

namespace uking::action {

NPCInfoOnHorse::NPCInfoOnHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCInfoOnHorse::~NPCInfoOnHorse() = default;

bool NPCInfoOnHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCInfoOnHorse::loadParams_() {}

}  // namespace uking::action

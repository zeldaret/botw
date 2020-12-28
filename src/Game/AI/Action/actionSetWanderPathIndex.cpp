#include "Game/AI/Action/actionSetWanderPathIndex.h"

namespace uking::action {

SetWanderPathIndex::SetWanderPathIndex(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetWanderPathIndex::~SetWanderPathIndex() = default;

bool SetWanderPathIndex::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetWanderPathIndex::loadParams_() {}

}  // namespace uking::action

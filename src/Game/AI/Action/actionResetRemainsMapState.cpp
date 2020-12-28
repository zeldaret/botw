#include "Game/AI/Action/actionResetRemainsMapState.h"

namespace uking::action {

ResetRemainsMapState::ResetRemainsMapState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ResetRemainsMapState::~ResetRemainsMapState() = default;

bool ResetRemainsMapState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetRemainsMapState::loadParams_() {}

}  // namespace uking::action

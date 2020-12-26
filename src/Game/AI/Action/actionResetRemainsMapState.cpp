#include "Game/AI/Action/actionResetRemainsMapState.h"

namespace uking::action {

ResetRemainsMapState::ResetRemainsMapState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ResetRemainsMapState::~ResetRemainsMapState() = default;

bool ResetRemainsMapState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetRemainsMapState::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ResetRemainsMapState::leave_() {
    ksys::act::ai::Action::leave_();
}

void ResetRemainsMapState::loadParams_() {}

void ResetRemainsMapState::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

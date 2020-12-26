#include "Game/AI/Action/actionSetWanderPathIndex.h"

namespace uking::action {

SetWanderPathIndex::SetWanderPathIndex(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetWanderPathIndex::~SetWanderPathIndex() = default;

bool SetWanderPathIndex::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetWanderPathIndex::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetWanderPathIndex::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetWanderPathIndex::loadParams_() {}

void SetWanderPathIndex::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

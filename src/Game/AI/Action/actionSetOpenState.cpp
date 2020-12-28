#include "Game/AI/Action/actionSetOpenState.h"

namespace uking::action {

SetOpenState::SetOpenState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetOpenState::~SetOpenState() = default;

bool SetOpenState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetOpenState::loadParams_() {
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
}

}  // namespace uking::action

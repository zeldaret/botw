#include "Game/AI/Action/actionSetExtraLifeOfPlayer.h"

namespace uking::action {

SetExtraLifeOfPlayer::SetExtraLifeOfPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetExtraLifeOfPlayer::~SetExtraLifeOfPlayer() = default;

bool SetExtraLifeOfPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetExtraLifeOfPlayer::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mProcessingMode_d, "ProcessingMode");
}

}  // namespace uking::action

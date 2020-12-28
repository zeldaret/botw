#include "Game/AI/Action/actionSetExtraEnergyOfPlayer.h"

namespace uking::action {

SetExtraEnergyOfPlayer::SetExtraEnergyOfPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetExtraEnergyOfPlayer::~SetExtraEnergyOfPlayer() = default;

bool SetExtraEnergyOfPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetExtraEnergyOfPlayer::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mProcessingMode_d, "ProcessingMode");
}

}  // namespace uking::action

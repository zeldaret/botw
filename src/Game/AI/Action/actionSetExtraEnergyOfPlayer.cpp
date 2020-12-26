#include "Game/AI/Action/actionSetExtraEnergyOfPlayer.h"

namespace uking::action {

SetExtraEnergyOfPlayer::SetExtraEnergyOfPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetExtraEnergyOfPlayer::~SetExtraEnergyOfPlayer() = default;

bool SetExtraEnergyOfPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetExtraEnergyOfPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetExtraEnergyOfPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetExtraEnergyOfPlayer::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mProcessingMode_d, "ProcessingMode");
}

void SetExtraEnergyOfPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

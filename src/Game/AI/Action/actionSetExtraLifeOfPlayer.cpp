#include "Game/AI/Action/actionSetExtraLifeOfPlayer.h"

namespace uking::action {

SetExtraLifeOfPlayer::SetExtraLifeOfPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetExtraLifeOfPlayer::~SetExtraLifeOfPlayer() = default;

bool SetExtraLifeOfPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetExtraLifeOfPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetExtraLifeOfPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetExtraLifeOfPlayer::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mProcessingMode_d, "ProcessingMode");
}

void SetExtraLifeOfPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

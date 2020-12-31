#include "Game/AI/AI/aiTowingPlayer.h"

namespace uking::ai {

TowingPlayer::TowingPlayer(const InitArg& arg) : Towing(arg) {}

TowingPlayer::~TowingPlayer() = default;

bool TowingPlayer::init_(sead::Heap* heap) {
    return Towing::init_(heap);
}

void TowingPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    Towing::enter_(params);
}

void TowingPlayer::leave_() {
    Towing::leave_();
}

void TowingPlayer::loadParams_() {
    Towing::loadParams_();
    getStaticParam(&mInterruptDef_s, "InterruptDef");
    getStaticParam(&mCheckPlayerStateDef_s, "CheckPlayerStateDef");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiGuardianMiniFindPlayer.h"

namespace uking::ai {

GuardianMiniFindPlayer::GuardianMiniFindPlayer(const InitArg& arg) : LandHumEnemyFindPlayer(arg) {}

GuardianMiniFindPlayer::~GuardianMiniFindPlayer() = default;

void GuardianMiniFindPlayer::loadParams_() {
    LandHumEnemyFindPlayer::loadParams_();
}

}  // namespace uking::ai

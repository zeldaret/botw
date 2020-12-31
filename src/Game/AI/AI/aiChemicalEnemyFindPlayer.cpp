#include "Game/AI/AI/aiChemicalEnemyFindPlayer.h"

namespace uking::ai {

ChemicalEnemyFindPlayer::ChemicalEnemyFindPlayer(const InitArg& arg)
    : LandHumEnemyFindPlayer(arg) {}

ChemicalEnemyFindPlayer::~ChemicalEnemyFindPlayer() = default;

void ChemicalEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyFindPlayer::enter_(params);
}

void ChemicalEnemyFindPlayer::leave_() {
    LandHumEnemyFindPlayer::leave_();
}

void ChemicalEnemyFindPlayer::loadParams_() {
    LandHumEnemyFindPlayer::loadParams_();
}

}  // namespace uking::ai

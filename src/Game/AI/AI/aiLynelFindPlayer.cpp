#include "Game/AI/AI/aiLynelFindPlayer.h"

namespace uking::ai {

LynelFindPlayer::LynelFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

LynelFindPlayer::~LynelFindPlayer() = default;

bool LynelFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void LynelFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void LynelFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void LynelFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

}  // namespace uking::ai

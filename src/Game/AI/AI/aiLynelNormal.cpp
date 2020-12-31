#include "Game/AI/AI/aiLynelNormal.h"

namespace uking::ai {

LynelNormal::LynelNormal(const InitArg& arg) : LandHumEnemyNormal(arg) {}

LynelNormal::~LynelNormal() = default;

bool LynelNormal::init_(sead::Heap* heap) {
    return LandHumEnemyNormal::init_(heap);
}

void LynelNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
}

void LynelNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void LynelNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
    getAITreeVariable(&mLynelAreaAlarmPoint_a, "LynelAreaAlarmPoint");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
    getAITreeVariable(&mLynelNoticeAttackRepeatNum_a, "LynelNoticeAttackRepeatNum");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiEnemyNoticeSoundSensitive.h"

namespace uking::ai {

EnemyNoticeSoundSensitive::EnemyNoticeSoundSensitive(const InitArg& arg)
    : EnemyNoticeSoundWithUI(arg) {}

EnemyNoticeSoundSensitive::~EnemyNoticeSoundSensitive() = default;

bool EnemyNoticeSoundSensitive::init_(sead::Heap* heap) {
    return EnemyNoticeSoundWithUI::init_(heap);
}

void EnemyNoticeSoundSensitive::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeSoundWithUI::enter_(params);
}

void EnemyNoticeSoundSensitive::leave_() {
    EnemyNoticeSoundWithUI::leave_();
}

void EnemyNoticeSoundSensitive::loadParams_() {
    EnemyNoticeSoundWithUI::loadParams_();
}

}  // namespace uking::ai

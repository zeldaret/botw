#include "Game/AI/AI/aiEnemyNoticeSoundWithUI.h"

namespace uking::ai {

EnemyNoticeSoundWithUI::EnemyNoticeSoundWithUI(const InitArg& arg) : EnemyNoticeSound(arg) {}

EnemyNoticeSoundWithUI::~EnemyNoticeSoundWithUI() = default;

bool EnemyNoticeSoundWithUI::init_(sead::Heap* heap) {
    return EnemyNoticeSound::init_(heap);
}

void EnemyNoticeSoundWithUI::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeSound::enter_(params);
}

void EnemyNoticeSoundWithUI::leave_() {
    EnemyNoticeSound::leave_();
}

void EnemyNoticeSoundWithUI::loadParams_() {
    EnemyNoticeSound::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiForestGiantNoticeSound.h"

namespace uking::ai {

ForestGiantNoticeSound::ForestGiantNoticeSound(const InitArg& arg) : EnemyNoticeSound(arg) {}

ForestGiantNoticeSound::~ForestGiantNoticeSound() = default;

bool ForestGiantNoticeSound::init_(sead::Heap* heap) {
    return EnemyNoticeSound::init_(heap);
}

void ForestGiantNoticeSound::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeSound::enter_(params);
}

void ForestGiantNoticeSound::leave_() {
    EnemyNoticeSound::leave_();
}

void ForestGiantNoticeSound::loadParams_() {
    EnemyNoticeSound::loadParams_();
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mUseSimpleOffset_s, "UseSimpleOffset");
}

}  // namespace uking::ai

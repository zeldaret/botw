#include "Game/AI/AI/aiEnemyNoticeLimit.h"

namespace uking::ai {

EnemyNoticeLimit::EnemyNoticeLimit(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyNoticeLimit::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNoticeLimit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNoticeLimit::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNoticeLimit::loadParams_() {
    getStaticParam(&mOverNum_s, "OverNum");
}

}  // namespace uking::ai

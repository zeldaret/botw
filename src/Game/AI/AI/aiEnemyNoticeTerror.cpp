#include "Game/AI/AI/aiEnemyNoticeTerror.h"

namespace uking::ai {

EnemyNoticeTerror::EnemyNoticeTerror(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoticeTerror::~EnemyNoticeTerror() = default;

bool EnemyNoticeTerror::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNoticeTerror::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNoticeTerror::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNoticeTerror::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mNoWarnDist_s, "NoWarnDist");
    getStaticParam(&mNoWarnHeightMin_s, "NoWarnHeightMin");
    getStaticParam(&mNoWarnHeightMax_s, "NoWarnHeightMax");
    getStaticParam(&mNoTerrorDist_s, "NoTerrorDist");
}

}  // namespace uking::ai

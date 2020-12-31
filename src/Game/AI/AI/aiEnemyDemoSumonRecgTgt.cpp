#include "Game/AI/AI/aiEnemyDemoSumonRecgTgt.h"

namespace uking::ai {

EnemyDemoSumonRecgTgt::EnemyDemoSumonRecgTgt(const InitArg& arg) : EnemyRecognizeTargetBase(arg) {}

EnemyDemoSumonRecgTgt::~EnemyDemoSumonRecgTgt() = default;

bool EnemyDemoSumonRecgTgt::init_(sead::Heap* heap) {
    return EnemyRecognizeTargetBase::init_(heap);
}

void EnemyDemoSumonRecgTgt::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRecognizeTargetBase::enter_(params);
}

void EnemyDemoSumonRecgTgt::leave_() {
    EnemyRecognizeTargetBase::leave_();
}

void EnemyDemoSumonRecgTgt::loadParams_() {
    EnemyRecognizeTargetBase::loadParams_();
    getStaticParam(&mOnlyOne_s, "OnlyOne");
    getStaticParam(&mIsBroadCastOnlyOne_s, "IsBroadCastOnlyOne");
    getStaticParam(&mDemoName_s, "DemoName");
    getStaticParam(&mEntryPoint_s, "EntryPoint");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiEnemyTargetInAreaSelect.h"

namespace uking::ai {

EnemyTargetInAreaSelect::EnemyTargetInAreaSelect(const InitArg& arg) : TargetInAreaSelect(arg) {}

EnemyTargetInAreaSelect::~EnemyTargetInAreaSelect() = default;

bool EnemyTargetInAreaSelect::init_(sead::Heap* heap) {
    return TargetInAreaSelect::init_(heap);
}

void EnemyTargetInAreaSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetInAreaSelect::enter_(params);
}

void EnemyTargetInAreaSelect::leave_() {
    TargetInAreaSelect::leave_();
}

void EnemyTargetInAreaSelect::loadParams_() {
    TargetInAreaSelect::loadParams_();
    getStaticParam(&mLengthXZ_s, "LengthXZ");
    getStaticParam(&mLengthMaxY_s, "LengthMaxY");
    getStaticParam(&mLengthMinY_s, "LengthMinY");
    getStaticParam(&mCentOffset_s, "CentOffset");
}

}  // namespace uking::ai

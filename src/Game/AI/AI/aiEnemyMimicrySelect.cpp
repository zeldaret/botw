#include "Game/AI/AI/aiEnemyMimicrySelect.h"

namespace uking::ai {

EnemyMimicrySelect::EnemyMimicrySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyMimicrySelect::~EnemyMimicrySelect() = default;

bool EnemyMimicrySelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyMimicrySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyMimicrySelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyMimicrySelect::loadParams_() {
    getMapUnitParam(&mIsMimicry_m, "IsMimicry");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

}  // namespace uking::ai

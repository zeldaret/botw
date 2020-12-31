#include "Game/AI/AI/aiKeeseNormal.h"

namespace uking::ai {

KeeseNormal::KeeseNormal(const InitArg& arg) : EnemyNormal(arg) {}

KeeseNormal::~KeeseNormal() = default;

bool KeeseNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void KeeseNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void KeeseNormal::leave_() {
    EnemyNormal::leave_();
}

void KeeseNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mRoamHeightFromGlowObj_s, "RoamHeightFromGlowObj");
    getMapUnitParam(&mIsCreateOnFace_m, "IsCreateOnFace");
}

}  // namespace uking::ai

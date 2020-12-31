#include "Game/AI/AI/aiMagneStickRoot.h"

namespace uking::ai {

MagneStickRoot::MagneStickRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MagneStickRoot::~MagneStickRoot() = default;

bool MagneStickRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MagneStickRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MagneStickRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MagneStickRoot::loadParams_() {
    getStaticParam(&mDefaultConnectionDistance_s, "DefaultConnectionDistance");
    getStaticParam(&mCollideRadiusFactor_s, "CollideRadiusFactor");
    getMapUnitParam(&mCollideRadius_m, "CollideRadius");
    getMapUnitParam(&mJoinSystemGroup_m, "JoinSystemGroup");
    getMapUnitParam(&mRegistFromBeginning_m, "RegistFromBeginning");
    getMapUnitParam(&mIgnoreObstacle_m, "IgnoreObstacle");
    getAITreeVariable(&mIsTargetFixedAcceptor_a, "IsTargetFixedAcceptor");
}

}  // namespace uking::ai

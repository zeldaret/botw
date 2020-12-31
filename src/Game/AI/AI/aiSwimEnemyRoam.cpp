#include "Game/AI/AI/aiSwimEnemyRoam.h"

namespace uking::ai {

SwimEnemyRoam::SwimEnemyRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwimEnemyRoam::~SwimEnemyRoam() = default;

void SwimEnemyRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwimEnemyRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwimEnemyRoam::loadParams_() {
    getStaticParam(&mRoamRadius_s, "RoamRadius");
    getStaticParam(&mRoamRatio_s, "RoamRatio");
    getStaticParam(&mRoamXRadius_s, "RoamXRadius");
    getStaticParam(&mRoamZRadius_s, "RoamZRadius");
}

}  // namespace uking::ai

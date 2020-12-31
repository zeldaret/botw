#include "Game/AI/AI/aiBalloonPlantNormal.h"

namespace uking::ai {

BalloonPlantNormal::BalloonPlantNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BalloonPlantNormal::~BalloonPlantNormal() = default;

bool BalloonPlantNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BalloonPlantNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BalloonPlantNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BalloonPlantNormal::loadParams_() {
    getStaticParam(&mRopeLength_s, "RopeLength");
    getStaticParam(&mRopeActorName_s, "RopeActorName");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiDogNormal.h"

namespace uking::ai {

DogNormal::DogNormal(const InitArg& arg) : DomesticNormal(arg) {}

DogNormal::~DogNormal() = default;

bool DogNormal::init_(sead::Heap* heap) {
    return DomesticNormal::init_(heap);
}

void DogNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    DomesticNormal::enter_(params);
}

void DogNormal::leave_() {
    DomesticNormal::leave_();
}

void DogNormal::loadParams_() {
    DomesticNormal::loadParams_();
    getStaticParam(&mNumFriendlyFoodForLeadTreasure_s, "NumFriendlyFoodForLeadTreasure");
    getStaticParam(&mMaxFollowDist_s, "MaxFollowDist");
    getStaticParam(&mMaxFollowFriendDecayRate_s, "MaxFollowFriendDecayRate");
    getStaticParam(&mFoodFriendRate_s, "FoodFriendRate");
    getStaticParam(&mFoodFriendDist_s, "FoodFriendDist");
    getStaticParam(&mNearFriendRate_s, "NearFriendRate");
    getStaticParam(&mNearFriendDist_s, "NearFriendDist");
    getStaticParam(&mFarFriendDecayRate_s, "FarFriendDecayRate");
    getStaticParam(&mFarFriendDist_s, "FarFriendDist");
    getStaticParam(&mFarFriendFriendlyDist_s, "FarFriendFriendlyDist");
    getStaticParam(&mAttackFriendDecayRate_s, "AttackFriendDecayRate");
    getStaticParam(&mFriendTickRate_s, "FriendTickRate");
    getStaticParam(&mNoMoveFriendDecayRate_s, "NoMoveFriendDecayRate");
    getStaticParam(&mNoMoveThreshold_s, "NoMoveThreshold");
    getStaticParam(&mFramesKeepMaxFriendly_s, "FramesKeepMaxFriendly");
    getStaticParam(&mFramesStayAfterLead_s, "FramesStayAfterLead");
    getStaticParam(&mAngleTurnToPlayer_s, "AngleTurnToPlayer");
}

}  // namespace uking::ai

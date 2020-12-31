#include "Game/AI/AI/aiUnarmedEnemySearch.h"

namespace uking::ai {

UnarmedEnemySearch::UnarmedEnemySearch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

UnarmedEnemySearch::~UnarmedEnemySearch() = default;

bool UnarmedEnemySearch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void UnarmedEnemySearch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void UnarmedEnemySearch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void UnarmedEnemySearch::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mTurnStartAng_s, "TurnStartAng");
}

}  // namespace uking::ai

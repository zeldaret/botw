#include "Game/AI/Action/actionPlayerInAreaAutoEnemyForbidTag.h"

namespace uking::action {

PlayerInAreaAutoEnemyForbidTag::PlayerInAreaAutoEnemyForbidTag(const InitArg& arg)
    : ForbidTag(arg) {}

PlayerInAreaAutoEnemyForbidTag::~PlayerInAreaAutoEnemyForbidTag() = default;

bool PlayerInAreaAutoEnemyForbidTag::init_(sead::Heap* heap) {
    return ForbidTag::init_(heap);
}

void PlayerInAreaAutoEnemyForbidTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ForbidTag::enter_(params);
}

void PlayerInAreaAutoEnemyForbidTag::leave_() {
    ForbidTag::leave_();
}

void PlayerInAreaAutoEnemyForbidTag::loadParams_() {
    ForbidTag::loadParams_();
    getMapUnitParam(&mNonAutoPlacementAnimal_m, "NonAutoPlacementAnimal");
    getMapUnitParam(&mNonAutoPlacementBird_m, "NonAutoPlacementBird");
    getMapUnitParam(&mNonAutoPlacementEnemy_m, "NonAutoPlacementEnemy");
    getMapUnitParam(&mNonAutoPlacementFish_m, "NonAutoPlacementFish");
    getMapUnitParam(&mNonAutoPlacementInsect_m, "NonAutoPlacementInsect");
    getMapUnitParam(&mNonAutoPlacementMaterial_m, "NonAutoPlacementMaterial");
    getMapUnitParam(&mNonEnemySearchPlayer_m, "NonEnemySearchPlayer");
}

void PlayerInAreaAutoEnemyForbidTag::calc_() {
    ForbidTag::calc_();
}

}  // namespace uking::action

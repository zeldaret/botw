#include "Game/Actor/Action/actionPlayerInAreaAutoEnemyForbidTag.h"

namespace uking::action {

PlayerInAreaAutoEnemyForbidTag::PlayerInAreaAutoEnemyForbidTag(const InitArg& arg)
    : BasicSignalForbidTag(arg) {}

PlayerInAreaAutoEnemyForbidTag::~PlayerInAreaAutoEnemyForbidTag() = default;

bool PlayerInAreaAutoEnemyForbidTag::init_(sead::Heap* heap) {
    return BasicSignalForbidTag::init_(heap);
}

void PlayerInAreaAutoEnemyForbidTag::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalForbidTag::enter_(params);
}

void PlayerInAreaAutoEnemyForbidTag::leave_() {
    BasicSignalForbidTag::leave_();
}

void PlayerInAreaAutoEnemyForbidTag::loadParams_() {
    BasicSignalForbidTag::loadParams_();
    getMapUnitParam(&mNonAutoPlacementAnimal_m, "NonAutoPlacementAnimal");
    getMapUnitParam(&mNonAutoPlacementBird_m, "NonAutoPlacementBird");
    getMapUnitParam(&mNonAutoPlacementEnemy_m, "NonAutoPlacementEnemy");
    getMapUnitParam(&mNonAutoPlacementFish_m, "NonAutoPlacementFish");
    getMapUnitParam(&mNonAutoPlacementInsect_m, "NonAutoPlacementInsect");
    getMapUnitParam(&mNonAutoPlacementMaterial_m, "NonAutoPlacementMaterial");
    getMapUnitParam(&mNonEnemySearchPlayer_m, "NonEnemySearchPlayer");
}

void PlayerInAreaAutoEnemyForbidTag::calc_() {
    BasicSignalForbidTag::calc_();
}

}  // namespace uking::action

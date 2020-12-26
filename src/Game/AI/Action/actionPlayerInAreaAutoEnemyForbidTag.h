#pragma once

#include "Game/AI/Action/actionForbidTag.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerInAreaAutoEnemyForbidTag : public ForbidTag {
    SEAD_RTTI_OVERRIDE(PlayerInAreaAutoEnemyForbidTag, ForbidTag)
public:
    explicit PlayerInAreaAutoEnemyForbidTag(const InitArg& arg);
    ~PlayerInAreaAutoEnemyForbidTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const bool* mNonAutoPlacementAnimal_m{};
    // map_unit_param at offset 0x28
    const bool* mNonAutoPlacementBird_m{};
    // map_unit_param at offset 0x30
    const bool* mNonAutoPlacementEnemy_m{};
    // map_unit_param at offset 0x38
    const bool* mNonAutoPlacementFish_m{};
    // map_unit_param at offset 0x40
    const bool* mNonAutoPlacementInsect_m{};
    // map_unit_param at offset 0x48
    const bool* mNonAutoPlacementMaterial_m{};
    // map_unit_param at offset 0x50
    const bool* mNonEnemySearchPlayer_m{};
};

}  // namespace uking::action

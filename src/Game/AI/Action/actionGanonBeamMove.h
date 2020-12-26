#pragma once

#include "Game/AI/Action/actionBeamMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonBeamMove : public BeamMove {
    SEAD_RTTI_OVERRIDE(GanonBeamMove, BeamMove)
public:
    explicit GanonBeamMove(const InitArg& arg);
    ~GanonBeamMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x70
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x78
    const int* mAttackPowerForPlayer_m{};
    // map_unit_param at offset 0x80
    const sead::Vector3f* mPosOffset_m{};
};

}  // namespace uking::action

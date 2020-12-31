#pragma once

#include "Game/AI/AI/aiKorokRailMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokTargetRailMove : public KorokRailMove {
    SEAD_RTTI_OVERRIDE(KorokTargetRailMove, KorokRailMove)
public:
    explicit KorokTargetRailMove(const InitArg& arg);
    ~KorokTargetRailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xc0
    const float* mRotSpd_s{};
    // map_unit_param at offset 0xc8
    const int* mKorokTargetAppearFrame_m{};
    // map_unit_param at offset 0xd0
    const int* mKorokTargetVanishFrame_m{};
    // map_unit_param at offset 0xd8
    const bool* mIsNoAppearEffect_m{};
};

}  // namespace uking::ai

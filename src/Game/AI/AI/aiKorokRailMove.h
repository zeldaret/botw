#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokRailMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokRailMove, ksys::act::ai::Ai)
public:
    explicit KorokRailMove(const InitArg& arg);
    ~KorokRailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mOnRailDistance_s{};
    // static_param at offset 0x40
    const float* mFarDistance_s{};
    // static_param at offset 0x48
    const bool* mIsIgnoreNoWaitStopPoint_s{};
    // map_unit_param at offset 0x50
    const float* mRailMoveSpeed_m{};
};

}  // namespace uking::ai

#pragma once

#include "Game/AI/Action/actionHornUseBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HornUse : public HornUseBase {
    SEAD_RTTI_OVERRIDE(HornUse, HornUseBase)
public:
    explicit HornUse(const InitArg& arg);
    ~HornUse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const int* mSpreadTime_s{};
    // static_param at offset 0x80
    const int* mTerrorLevel_s{};
    // static_param at offset 0x88
    const float* mSpreadDist_s{};
    // static_param at offset 0x90
    const int* mNoticeMaskState_s{};
};

}  // namespace uking::action

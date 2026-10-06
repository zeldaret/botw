#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NewRangeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NewRangeSelect, ksys::act::ai::Ai)
public:
    explicit NewRangeSelect(const InitArg& arg);
    ~NewRangeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mFarDist_s{};
    // static_param at offset 0x48
    const bool* mIsSelectEveryFrame_s{};
};

}  // namespace uking::ai

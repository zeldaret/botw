#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RestLifeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RestLifeSelect, ksys::act::ai::Ai)
public:
    explicit RestLifeSelect(const InitArg& arg);
    ~RestLifeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mLifeRatio_s{};
    // static_param at offset 0x40
    const bool* mIsTrgOnly_s{};
    // static_param at offset 0x48
    const bool* mIsEnter_s{};
};

}  // namespace uking::ai

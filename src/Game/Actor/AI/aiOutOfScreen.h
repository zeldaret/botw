#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OutOfScreen : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OutOfScreen, ksys::act::ai::Ai)
public:
    explicit OutOfScreen(const InitArg& arg);
    ~OutOfScreen() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mUpdateInterval_s{};
    // static_param at offset 0x40
    const float* mTagetDistance_s{};
    // static_param at offset 0x48
    const float* mDeleteDistance_s{};
};

}  // namespace uking::ai

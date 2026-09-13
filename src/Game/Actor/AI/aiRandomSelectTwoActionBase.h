#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RandomSelectTwoActionBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RandomSelectTwoActionBase, ksys::act::ai::Ai)
public:
    explicit RandomSelectTwoActionBase(const InitArg& arg);
    ~RandomSelectTwoActionBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCorrectRateToA_s{};
    // static_param at offset 0x40
    const int* mCorrectRateToB_s{};
};

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSpearLifeSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSpearLifeSelector, ksys::act::ai::Ai)
public:
    explicit SiteBossSpearLifeSelector(const InitArg& arg);
    ~SiteBossSpearLifeSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mPatternChangeLife2_s{};
    // static_param at offset 0x40
    const float* mPatternChangeLife3_s{};
};

}  // namespace uking::ai

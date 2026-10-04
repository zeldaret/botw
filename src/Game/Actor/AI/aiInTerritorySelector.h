#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InTerritorySelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InTerritorySelector, ksys::act::ai::Ai)
public:
    explicit InTerritorySelector(const InitArg& arg);
    ~InTerritorySelector() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTerritoryArea_s{};
};

}  // namespace uking::ai

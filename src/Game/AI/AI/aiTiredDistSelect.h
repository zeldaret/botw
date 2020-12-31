#pragma once

#include "Game/AI/AI/aiTargetHomeRangeSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TiredDistSelect : public TargetHomeRangeSelect {
    SEAD_RTTI_OVERRIDE(TiredDistSelect, TargetHomeRangeSelect)
public:
    explicit TiredDistSelect(const InitArg& arg);
    ~TiredDistSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x50
    const float* mTerritoryArea_m{};
};

}  // namespace uking::ai

#pragma once

#include "Game/AI/AI/aiRangeSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetRangeSelect : public RangeSelect {
    SEAD_RTTI_OVERRIDE(TargetRangeSelect, RangeSelect)
public:
    explicit TargetRangeSelect(const InitArg& arg);
    ~TargetRangeSelect() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const bool* mIsXZOnly_s{};
};

}  // namespace uking::ai

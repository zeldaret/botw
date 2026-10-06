#pragma once

#include "Game/Actor/AI/aiNewRangeSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetHomeRangeSelect : public NewRangeSelect {
    SEAD_RTTI_OVERRIDE(TargetHomeRangeSelect, NewRangeSelect)
public:
    explicit TargetHomeRangeSelect(const InitArg& arg);
    ~TargetHomeRangeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

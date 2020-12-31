#pragma once

#include "Game/AI/AI/aiInWaterSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InWaterKeepSelect : public InWaterSelect {
    SEAD_RTTI_OVERRIDE(InWaterKeepSelect, InWaterSelect)
public:
    explicit InWaterKeepSelect(const InitArg& arg);
    ~InWaterKeepSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x58
    bool* mIsKeepInWater_a{};
};

}  // namespace uking::ai

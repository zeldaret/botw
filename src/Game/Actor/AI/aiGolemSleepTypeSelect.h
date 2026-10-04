#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemSleepTypeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolemSleepTypeSelect, ksys::act::ai::Ai)
public:
    explicit GolemSleepTypeSelect(const InitArg& arg);
    ~GolemSleepTypeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    sead::SafeString mGolemSleepType_m{};
};

}  // namespace uking::ai

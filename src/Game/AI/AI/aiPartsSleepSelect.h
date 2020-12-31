#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PartsSleepSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PartsSleepSelect, ksys::act::ai::Ai)
public:
    explicit PartsSleepSelect(const InitArg& arg);
    ~PartsSleepSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mPartsName_s{};
};

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalPartsHasSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalPartsHasSelect, ksys::act::ai::Ai)
public:
    explicit StalPartsHasSelect(const InitArg& arg);
    ~StalPartsHasSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mPartsID_s{};
};

}  // namespace uking::ai

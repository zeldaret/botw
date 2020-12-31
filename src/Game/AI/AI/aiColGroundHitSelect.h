#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ColGroundHitSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ColGroundHitSelect, ksys::act::ai::Ai)
public:
    explicit ColGroundHitSelect(const InitArg& arg);
    ~ColGroundHitSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsCheckEachFrame_s{};
};

}  // namespace uking::ai

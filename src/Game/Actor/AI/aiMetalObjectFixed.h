#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MetalObjectFixed : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MetalObjectFixed, ksys::act::ai::Ai)
public:
    explicit MetalObjectFixed(const InitArg& arg);
    ~MetalObjectFixed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsFixedPlace_m{};
};

}  // namespace uking::ai

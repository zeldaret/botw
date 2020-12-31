#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ItemRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ItemRoot, ksys::act::ai::Ai)
public:
    explicit ItemRoot(const InitArg& arg);
    ~ItemRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAtHitImpulseRate_s{};
    // map_unit_param at offset 0x40
    const int* mInitMotionStatus_m{};
};

}  // namespace uking::ai

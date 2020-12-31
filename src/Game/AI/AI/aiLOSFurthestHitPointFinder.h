#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LOSFurthestHitPointFinder : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LOSFurthestHitPointFinder, ksys::act::ai::Ai)
public:
    explicit LOSFurthestHitPointFinder(const InitArg& arg);
    ~LOSFurthestHitPointFinder() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x10];
    // static_param at offset 0x48
    const int* mMaxNumCheck_s{};
    // static_param at offset 0x50
    const float* mCheckDistance_s{};
    // static_param at offset 0x58
    const bool* mOnlyCheckBehind_s{};
    // static_param at offset 0x60
    const bool* mUseActionB_s{};
};

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossBowChildDeviceRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossBowChildDeviceRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossBowChildDeviceRoot(const InitArg& arg);
    ~SiteBossBowChildDeviceRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mXRotateSpeed_s{};
    // static_param at offset 0x40
    const float* mSlowRate_s{};
    // map_unit_param at offset 0x48
    const int* mCount_m{};
};

}  // namespace uking::ai

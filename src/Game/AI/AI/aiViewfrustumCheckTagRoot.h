#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ViewfrustumCheckTagRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ViewfrustumCheckTagRoot, ksys::act::ai::Ai)
public:
    explicit ViewfrustumCheckTagRoot(const InitArg& arg);
    ~ViewfrustumCheckTagRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mAllwaysOnDisFromPlayer_m{};
    // map_unit_param at offset 0x40
    const float* mAllwaysOnCamDir_m{};
};

}  // namespace uking::ai

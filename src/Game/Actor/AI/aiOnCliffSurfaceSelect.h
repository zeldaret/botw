#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OnCliffSurfaceSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OnCliffSurfaceSelect, ksys::act::ai::Ai)
public:
    explicit OnCliffSurfaceSelect(const InitArg& arg);
    ~OnCliffSurfaceSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mOnCliff_m{};
    // aitree_variable at offset 0x40
    bool* mIsCliffFreeze_a{};
};

}  // namespace uking::ai

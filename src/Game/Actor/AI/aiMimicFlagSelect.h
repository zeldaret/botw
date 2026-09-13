#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MimicFlagSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MimicFlagSelect, ksys::act::ai::Ai)
public:
    explicit MimicFlagSelect(const InitArg& arg);
    ~MimicFlagSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsMimicry_m{};
};

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PointWindTagRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PointWindTagRoot, ksys::act::ai::Ai)
public:
    explicit PointWindTagRoot(const InitArg& arg);
    ~PointWindTagRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mDirection_m{};
    // map_unit_param at offset 0x40
    const float* mWindSpeed_m{};
    // map_unit_param at offset 0x48
    sead::SafeString mShape_m{};
};

}  // namespace uking::ai

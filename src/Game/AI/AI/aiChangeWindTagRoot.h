#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChangeWindTagRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChangeWindTagRoot, ksys::act::ai::Ai)
public:
    explicit ChangeWindTagRoot(const InitArg& arg);
    ~ChangeWindTagRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mDirection_m{};
    // map_unit_param at offset 0x40
    const float* mWindSpeed_m{};
};

}  // namespace uking::ai

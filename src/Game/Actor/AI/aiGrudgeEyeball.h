#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GrudgeEyeball : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GrudgeEyeball, ksys::act::ai::Ai)
public:
    explicit GrudgeEyeball(const InitArg& arg);
    ~GrudgeEyeball() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mEyeballFirstState_m{};
};

}  // namespace uking::ai

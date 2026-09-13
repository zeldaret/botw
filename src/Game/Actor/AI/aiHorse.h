#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Horse : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Horse, ksys::act::ai::Ai)
public:
    explicit Horse(const InitArg& arg);
    ~Horse() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDistanceFall_s{};
    // static_param at offset 0x40
    const float* mDistanceFallDie_s{};
};

}  // namespace uking::ai

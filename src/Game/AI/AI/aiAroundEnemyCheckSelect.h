#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AroundEnemyCheckSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AroundEnemyCheckSelect, ksys::act::ai::Ai)
public:
    explicit AroundEnemyCheckSelect(const InitArg& arg);
    ~AroundEnemyCheckSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCheckDist_s{};
};

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class IsPlacementAreaEnemy : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(IsPlacementAreaEnemy, ksys::act::ai::Ai)
public:
    explicit IsPlacementAreaEnemy(const InitArg& arg);
    ~IsPlacementAreaEnemy() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCheckType_s{};
};

}  // namespace uking::ai

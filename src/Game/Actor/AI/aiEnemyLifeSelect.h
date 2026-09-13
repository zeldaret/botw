#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyLifeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyLifeSelect, ksys::act::ai::Ai)
public:
    explicit EnemyLifeSelect(const InitArg& arg);
    ~EnemyLifeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsWatchKeeping_m{};
};

}  // namespace uking::ai

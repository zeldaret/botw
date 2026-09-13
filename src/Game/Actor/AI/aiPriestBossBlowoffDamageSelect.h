#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossBlowoffDamageSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossBlowoffDamageSelect, ksys::act::ai::Ai)
public:
    explicit PriestBossBlowoffDamageSelect(const InitArg& arg);
    ~PriestBossBlowoffDamageSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

#pragma once

#include "Game/AI/AI/aiDieSelectChemShockPlus.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeeseDieSelect : public DieSelectChemShockPlus {
    SEAD_RTTI_OVERRIDE(KeeseDieSelect, DieSelectChemShockPlus)
public:
    explicit KeeseDieSelect(const InitArg& arg);
    ~KeeseDieSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

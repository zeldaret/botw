#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemChemicalResetSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolemChemicalResetSelect, ksys::act::ai::Ai)
public:
    explicit GolemChemicalResetSelect(const InitArg& arg);
    ~GolemChemicalResetSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mGolemChemicalController_a{};
};

}  // namespace uking::ai

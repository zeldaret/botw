#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class VacuumedBombDamageSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(VacuumedBombDamageSelect, ksys::act::ai::Ai)
public:
    explicit VacuumedBombDamageSelect(const InitArg& arg);
    ~VacuumedBombDamageSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mVacuumedExplodingBomb_a{};
};

}  // namespace uking::ai

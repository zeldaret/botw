#pragma once

#include "Game/AI/AI/aiGiantArmorRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChemicalGiantArmorRoot : public GiantArmorRoot {
    SEAD_RTTI_OVERRIDE(ChemicalGiantArmorRoot, GiantArmorRoot)
public:
    explicit ChemicalGiantArmorRoot(const InitArg& arg);
    ~ChemicalGiantArmorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mElectricTime_s{};
    // static_param at offset 0x40
    const float* mElectricDamageScale_s{};
};

}  // namespace uking::ai

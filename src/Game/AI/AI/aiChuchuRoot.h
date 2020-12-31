#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChuchuRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(ChuchuRoot, EnemyRoot)
public:
    explicit ChuchuRoot(const InitArg& arg);
    ~ChuchuRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const int* mSubASSlot_s{};
    // static_param at offset 0x1e0
    const int* mChemicalScaleTime_s{};
    // static_param at offset 0x1e8
    const float* mClothStiffness30_s{};
    // static_param at offset 0x1f0
    const float* mClothStiffness20_s{};
    // static_param at offset 0x1f8
    sead::SafeString mSubAS_s{};
    // static_param at offset 0x208
    sead::SafeString mChemicalFieldKey_s{};
};

}  // namespace uking::ai

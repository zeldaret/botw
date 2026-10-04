#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyMimicrySelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyMimicrySelect, ksys::act::ai::Ai)
public:
    explicit EnemyMimicrySelect(const InitArg& arg);
    ~EnemyMimicrySelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsMimicry_m{};
    // aitree_variable at offset 0x40
    int* mMimicryMaterial_a{};
    // aitree_variable at offset 0x48
    bool* mIsStartResetMimicry_a{};
};

}  // namespace uking::ai

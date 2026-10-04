#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MimicCliffStopEnemyNormalBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MimicCliffStopEnemyNormalBase, ksys::act::ai::Ai)
public:
    explicit MimicCliffStopEnemyNormalBase(const InitArg& arg);
    ~MimicCliffStopEnemyNormalBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mNoticeSoundTime_s{};
    // static_param at offset 0x40
    const float* mOffsetHand_s{};
    // static_param at offset 0x48
    const float* mOffsetTail_s{};
    // static_param at offset 0x50
    const float* mOffsetHandRotBase_s{};
    // aitree_variable at offset 0x58
    int* mMimicryMaterial_a{};
    // aitree_variable at offset 0x60
    bool* mIsStartResetMimicry_a{};
    // aitree_variable at offset 0x68
    bool* mIsCliffFreeze_a{};
};

}  // namespace uking::ai

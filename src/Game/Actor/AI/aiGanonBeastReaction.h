#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBeastReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBeastReaction, ksys::act::ai::Ai)
public:
    explicit GanonBeastReaction(const InitArg& arg);
    ~GanonBeastReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mASSlot_s{};
    // aitree_variable at offset 0x40
    bool* mIsWeakPointAppearMode_a{};
    // aitree_variable at offset 0x48
    void* mWeakPointAliveFlag_a{};
    // aitree_variable at offset 0x50
    void* mWeakPointActiveFlag_a{};
};

}  // namespace uking::ai

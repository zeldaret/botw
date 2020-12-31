#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemoteBomb : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemoteBomb, ksys::act::ai::Ai)
public:
    explicit RemoteBomb(const InitArg& arg);
    ~RemoteBomb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mWindRatio_s{};
    // static_param at offset 0x40
    sead::SafeString mXLinkKey_s{};
    // aitree_variable at offset 0x50
    bool* mIsIgniteCarriedBomb_a{};
};

}  // namespace uking::ai

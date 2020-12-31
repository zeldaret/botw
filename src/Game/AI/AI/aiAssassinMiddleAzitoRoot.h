#pragma once

#include "Game/AI/AI/aiAssassinNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleAzitoRoot : public AssassinNormal {
    SEAD_RTTI_OVERRIDE(AssassinMiddleAzitoRoot, AssassinNormal)
public:
    explicit AssassinMiddleAzitoRoot(const InitArg& arg);
    ~AssassinMiddleAzitoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x420
    sead::SafeString mEntryPoint_s{};
    // static_param at offset 0x430
    sead::SafeString mDemoName_s{};
    // static_param at offset 0x440
    sead::SafeString mLikeItem_s{};
};

}  // namespace uking::ai

#pragma once

#include "Game/AI/AI/aiAssassinMiddleRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleAzitoRootAccept : public AssassinMiddleRoot {
    SEAD_RTTI_OVERRIDE(AssassinMiddleAzitoRootAccept, AssassinMiddleRoot)
public:
    explicit AssassinMiddleAzitoRootAccept(const InitArg& arg);
    ~AssassinMiddleAzitoRootAccept() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x340
    sead::SafeString mEntryPoint_s{};
    // static_param at offset 0x350
    sead::SafeString mDemoName_s{};
};

}  // namespace uking::ai

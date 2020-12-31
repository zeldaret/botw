#pragma once

#include "Game/AI/AI/aiReuseBulletPartsRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemPartRoot : public ReuseBulletPartsRoot {
    SEAD_RTTI_OVERRIDE(GolemPartRoot, ReuseBulletPartsRoot)
public:
    explicit GolemPartRoot(const InitArg& arg);
    ~GolemPartRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const float* mChemFieldScale_s{};
    // static_param at offset 0x98
    sead::SafeString mNormalAS_s{};
    // static_param at offset 0xa8
    sead::SafeString mActiveAS_s{};
    // aitree_variable at offset 0xb8
    bool* mGolemPartInitialIceMagic_a{};
    // aitree_variable at offset 0xc0
    bool* mGolemPartInitialBurn_a{};
};

}  // namespace uking::ai

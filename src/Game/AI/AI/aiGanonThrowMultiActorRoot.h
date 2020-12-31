#pragma once

#include "Game/AI/AI/aiGanonThrowActorRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonThrowMultiActorRoot : public GanonThrowActorRoot {
    SEAD_RTTI_OVERRIDE(GanonThrowMultiActorRoot, GanonThrowActorRoot)
public:
    explicit GanonThrowMultiActorRoot(const InitArg& arg);
    ~GanonThrowMultiActorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xa8
    sead::SafeString mPartsName1_s{};
    // static_param at offset 0xb8
    sead::SafeString mPartsName2_s{};
    // static_param at offset 0xc8
    sead::SafeString mPartsName3_s{};
    // static_param at offset 0xd8
    sead::SafeString mPartsName4_s{};
    // static_param at offset 0xe8
    sead::SafeString mPartsName5_s{};
    // static_param at offset 0xf8
    sead::SafeString mPartsName6_s{};
    // static_param at offset 0x108
    sead::SafeString mPartsName7_s{};
    // static_param at offset 0x118
    sead::SafeString mPartsName8_s{};
};

}  // namespace uking::ai

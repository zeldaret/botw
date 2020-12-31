#pragma once

#include "Game/AI/AI/aiRemainsRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsFireRoot : public RemainsRoot {
    SEAD_RTTI_OVERRIDE(RemainsFireRoot, RemainsRoot)
public:
    explicit RemainsFireRoot(const InitArg& arg);
    ~RemainsFireRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    sead::SafeString mTargetBoneName_s{};
};

}  // namespace uking::ai

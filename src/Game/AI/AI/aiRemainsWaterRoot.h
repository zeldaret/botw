#pragma once

#include "Game/AI/AI/aiRemainsRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWaterRoot : public RemainsRoot {
    SEAD_RTTI_OVERRIDE(RemainsWaterRoot, RemainsRoot)
public:
    explicit RemainsWaterRoot(const InitArg& arg);
    ~RemainsWaterRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x50
    void* mRemainsWaterBattleInfo_a{};
};

}  // namespace uking::ai

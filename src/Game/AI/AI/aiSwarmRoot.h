#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwarmRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(SwarmRoot, EnemyRoot)
public:
    explicit SwarmRoot(const InitArg& arg);
    ~SwarmRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    sead::SafeString mASName_s{};
};

}  // namespace uking::ai

#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MiniGolemReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(MiniGolemReaction, EnemyDefaultReaction)
public:
    explicit MiniGolemReaction(const InitArg& arg);
    ~MiniGolemReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x68
    void* mGolemChemicalController_a{};
};

}  // namespace uking::ai

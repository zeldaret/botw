#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AirOctaReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(AirOctaReaction, EnemyDefaultReaction)
public:
    explicit AirOctaReaction(const InitArg& arg);
    ~AirOctaReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x68
    void* mAirOctaDataMgr_a{};
};

}  // namespace uking::ai

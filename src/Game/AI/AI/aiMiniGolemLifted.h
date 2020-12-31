#pragma once

#include "Game/AI/AI/aiEnemyLifted.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MiniGolemLifted : public EnemyLifted {
    SEAD_RTTI_OVERRIDE(MiniGolemLifted, EnemyLifted)
public:
    explicit MiniGolemLifted(const InitArg& arg);
    ~MiniGolemLifted() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x70
    void* mGolemChemicalController_a{};
};

}  // namespace uking::ai

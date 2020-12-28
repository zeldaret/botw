#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OkAutoPlacementEnemyDeadlyQuest : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OkAutoPlacementEnemyDeadlyQuest, ksys::act::ai::Action)
public:
    explicit OkAutoPlacementEnemyDeadlyQuest(const InitArg& arg);
    ~OkAutoPlacementEnemyDeadlyQuest() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action

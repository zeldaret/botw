#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockRootBase : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(OctarockRootBase, EnemyRoot)
public:
    explicit OctarockRootBase(const InitArg& arg);
    ~OctarockRootBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

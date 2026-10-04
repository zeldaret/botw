#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCPurchaseEnemyMaterial : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCPurchaseEnemyMaterial, ksys::act::ai::Action)
public:
    explicit NPCPurchaseEnemyMaterial(const InitArg& arg);
    ~NPCPurchaseEnemyMaterial() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action

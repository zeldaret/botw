#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCDyeShopCloseMaterial : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCDyeShopCloseMaterial, ksys::act::ai::Action)
public:
    explicit NPCDyeShopCloseMaterial(const InitArg& arg);
    ~NPCDyeShopCloseMaterial() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action

#pragma once

#include "Game/AI/Action/actionWaterFloatFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceRagdollOffWaterFloatFreeze : public WaterFloatFreeze {
    SEAD_RTTI_OVERRIDE(ForceRagdollOffWaterFloatFreeze, WaterFloatFreeze)
public:
    explicit ForceRagdollOffWaterFloatFreeze(const InitArg& arg);
    ~ForceRagdollOffWaterFloatFreeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x78
    void* mCRBOffsetUnit_a{};
};

}  // namespace uking::action

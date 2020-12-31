#pragma once

#include "Game/AI/AI/aiGolemRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MiniGolemRoot : public GolemRootBase {
    SEAD_RTTI_OVERRIDE(MiniGolemRoot, GolemRootBase)
public:
    explicit MiniGolemRoot(const InitArg& arg);
    ~MiniGolemRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x310
    bool* mIsAllowReactionLift_a{};
    // static_param at offset 0x318
    const int* mLiftDeadTime_s{};
};

}  // namespace uking::ai

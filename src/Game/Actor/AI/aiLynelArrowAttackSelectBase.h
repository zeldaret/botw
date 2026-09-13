#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelArrowAttackSelectBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelArrowAttackSelectBase, ksys::act::ai::Ai)
public:
    explicit LynelArrowAttackSelectBase(const InitArg& arg);
    ~LynelArrowAttackSelectBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    int* mLynelAIFlags_a{};
};

}  // namespace uking::ai

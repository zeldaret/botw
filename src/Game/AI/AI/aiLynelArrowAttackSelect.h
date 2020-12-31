#pragma once

#include "Game/AI/AI/aiLynelArrowAttackSelectBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelArrowAttackSelect : public LynelArrowAttackSelectBase {
    SEAD_RTTI_OVERRIDE(LynelArrowAttackSelect, LynelArrowAttackSelectBase)
public:
    explicit LynelArrowAttackSelect(const InitArg& arg);
    ~LynelArrowAttackSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

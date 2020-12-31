#pragma once

#include "Game/AI/AI/aiLynelArrowAttackSelectBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelArrowAttackSelectOnce : public LynelArrowAttackSelectBase {
    SEAD_RTTI_OVERRIDE(LynelArrowAttackSelectOnce, LynelArrowAttackSelectBase)
public:
    explicit LynelArrowAttackSelectOnce(const InitArg& arg);
    ~LynelArrowAttackSelectOnce() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

#pragma once

#include "Game/Actor/AI/aiBigCannon.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GoronCannon : public BigCannon {
    SEAD_RTTI_OVERRIDE(GoronCannon, BigCannon)
public:
    explicit GoronCannon(const InitArg& arg);
    ~GoronCannon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

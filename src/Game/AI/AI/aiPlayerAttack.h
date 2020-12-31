#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerAttack, ksys::act::ai::Ai)
public:
    explicit PlayerAttack(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

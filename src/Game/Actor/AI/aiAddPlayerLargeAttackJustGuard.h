#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddPlayerLargeAttackJustGuard : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AddPlayerLargeAttackJustGuard, ksys::act::ai::Ai)
public:
    explicit AddPlayerLargeAttackJustGuard(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai

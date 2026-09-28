#pragma once

#include "Game/Actor/AI/aiTargetHeightAreaSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleMagicAfter : public TargetHeightAreaSelect {
    SEAD_RTTI_OVERRIDE(AssassinMiddleMagicAfter, TargetHeightAreaSelect)
public:
    explicit AssassinMiddleMagicAfter(const InitArg& arg);
    ~AssassinMiddleMagicAfter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x50
    bool* mIsInterseptAttack_a{};
};

}  // namespace uking::ai

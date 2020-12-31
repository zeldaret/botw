#pragma once

#include "Game/AI/AI/aiPreyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KokkoRoot : public PreyRoot {
    SEAD_RTTI_OVERRIDE(KokkoRoot, PreyRoot)
public:
    explicit KokkoRoot(const InitArg& arg);
    ~KokkoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x208
    const int* mStartSpecialAttackCount_s{};
    // static_param at offset 0x210
    sead::SafeString mAvoidCountActorName_s{};
};

}  // namespace uking::ai

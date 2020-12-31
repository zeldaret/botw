#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(OctarockReaction, EnemyDefaultReaction)
public:
    explicit OctarockReaction(const InitArg& arg);
    ~OctarockReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const bool* mIsWigBreackByGust_s{};
    // aitree_variable at offset 0x70
    void* mOctarockFormChangeUnit_a{};
};

}  // namespace uking::ai

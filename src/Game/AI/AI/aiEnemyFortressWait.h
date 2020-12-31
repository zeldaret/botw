#pragma once

#include "Game/AI/AI/aiEnemyWaitViewItem.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFortressWait : public EnemyWaitViewItem {
    SEAD_RTTI_OVERRIDE(EnemyFortressWait, EnemyWaitViewItem)
public:
    explicit EnemyFortressWait(const InitArg& arg);
    ~EnemyFortressWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x40
    const int* mFortressEatPer_m{};
    // map_unit_param at offset 0x48
    sead::SafeString mFortressEatItem_m{};
    // static_param at offset 0x58
    const int* mEatPer_s{};
    // static_param at offset 0x60
    sead::SafeString mEatItem_s{};
};

}  // namespace uking::ai

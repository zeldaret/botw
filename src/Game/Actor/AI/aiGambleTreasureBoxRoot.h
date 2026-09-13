#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GambleTreasureBoxRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GambleTreasureBoxRoot, ksys::act::ai::Ai)
public:
    explicit GambleTreasureBoxRoot(const InitArg& arg);
    ~GambleTreasureBoxRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    bool* mIsOpenTreasureBox_a{};
    // aitree_variable at offset 0x40
    sead::SafeString* mDropActorName_a{};
};

}  // namespace uking::ai

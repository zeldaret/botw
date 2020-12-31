#pragma once

#include "Game/AI/AI/aiViewWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OnCliffViewWait : public ViewWait {
    SEAD_RTTI_OVERRIDE(OnCliffViewWait, ViewWait)
public:
    explicit OnCliffViewWait(const InitArg& arg);
    ~OnCliffViewWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x60
    const bool* mOnCliffTurn_m{};
};

}  // namespace uking::ai

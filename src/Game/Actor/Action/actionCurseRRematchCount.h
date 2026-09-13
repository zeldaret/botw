#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CurseRRematchCount : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CurseRRematchCount, ksys::act::ai::Action)
public:
    explicit CurseRRematchCount(const InitArg& arg);
    ~CurseRRematchCount() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    bool oneShot_() override;

    // dynamic_param at offset 0x20
    int* mRematchCount_d{};
    // dynamic_param at offset 0x28
    int* mCurseRType_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataStringCounterName_d{};
};

}  // namespace uking::action

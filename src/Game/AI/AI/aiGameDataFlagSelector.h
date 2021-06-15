#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GameDataFlagSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GameDataFlagSelector, ksys::act::ai::Ai)
public:
    explicit GameDataFlagSelector(const InitArg& arg);
    ~GameDataFlagSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mCheckOnEnterOnly_s{};
    // map_unit_param at offset 0x40
    sead::SafeString mClearFlag_m{};
};

}  // namespace uking::ai

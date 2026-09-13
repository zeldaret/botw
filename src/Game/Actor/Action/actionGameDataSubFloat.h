#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GameDataSubFloat : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GameDataSubFloat, ksys::act::ai::Action)
public:
    explicit GameDataSubFloat(const InitArg& arg);
    ~GameDataSubFloat() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataFloatSrcName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataFloatDstName_d{};
    // dynamic_param at offset 0x40
    sead::SafeString mGameDataFloatToName_d{};
};

}  // namespace uking::action

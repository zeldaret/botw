#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GameDataAddFloat : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GameDataAddFloat, ksys::act::ai::Action)
public:
    explicit GameDataAddFloat(const InitArg& arg);
    ~GameDataAddFloat() override;

    bool oneShot_() override;
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

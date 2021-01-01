#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GameDataAddInt : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GameDataAddInt, ksys::act::ai::Action)
public:
    explicit GameDataAddInt(const InitArg& arg);
    ~GameDataAddInt() override;

    bool oneShot_() override;
    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataIntSrcName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataIntDstName_d{};
    // dynamic_param at offset 0x40
    sead::SafeString mGameDataIntToName_d{};
};

}  // namespace uking::action

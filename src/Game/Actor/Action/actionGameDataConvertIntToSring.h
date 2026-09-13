#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GameDataConvertIntToSring : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GameDataConvertIntToSring, ksys::act::ai::Action)
public:
    explicit GameDataConvertIntToSring(const InitArg& arg);
    ~GameDataConvertIntToSring() override;

    bool oneShot_() override;
    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataIntInput_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataStringOutput_d{};
};

}  // namespace uking::action

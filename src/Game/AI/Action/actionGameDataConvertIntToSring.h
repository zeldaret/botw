#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GameDataConvertIntToSring : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GameDataConvertIntToSring, ksys::act::ai::Action)
public:
    explicit GameDataConvertIntToSring(const InitArg& arg);
    ~GameDataConvertIntToSring() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString* mGameDataIntInput_d{};
    // dynamic_param at offset 0x30
    sead::SafeString* mGameDataStringOutput_d{};
};

}  // namespace uking::action

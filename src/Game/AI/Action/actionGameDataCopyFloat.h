#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GameDataCopyFloat : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GameDataCopyFloat, ksys::act::ai::Action)
public:
    explicit GameDataCopyFloat(const InitArg& arg);
    ~GameDataCopyFloat() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataFloatSrcName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataFloatDstName_d{};
};

}  // namespace uking::action

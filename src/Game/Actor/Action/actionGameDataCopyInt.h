#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GameDataCopyInt : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GameDataCopyInt, ksys::act::ai::Action)
public:
    explicit GameDataCopyInt(const InitArg& arg);
    ~GameDataCopyInt() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataIntSrcName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataIntDstName_d{};
};

}  // namespace uking::action

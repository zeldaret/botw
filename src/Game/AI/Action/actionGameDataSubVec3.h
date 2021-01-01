#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GameDataSubVec3 : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GameDataSubVec3, ksys::act::ai::Action)
public:
    explicit GameDataSubVec3(const InitArg& arg);
    ~GameDataSubVec3() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataVec3fSrcName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataVec3fDstName_d{};
    // dynamic_param at offset 0x40
    sead::SafeString mGameDataVec3fToName_d{};
};

}  // namespace uking::action

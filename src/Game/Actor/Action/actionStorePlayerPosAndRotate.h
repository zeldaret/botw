#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StorePlayerPosAndRotate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StorePlayerPosAndRotate, ksys::act::ai::Action)
public:
    explicit StorePlayerPosAndRotate(const InitArg& arg);
    ~StorePlayerPosAndRotate() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataVec3fPlayerPos_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataFloatPlayerDirectionY_d{};
};

}  // namespace uking::action

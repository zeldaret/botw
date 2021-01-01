#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RestorePlayerPosAndRotate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RestorePlayerPosAndRotate, ksys::act::ai::Action)
public:
    explicit RestorePlayerPosAndRotate(const InitArg& arg);
    ~RestorePlayerPosAndRotate() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataVec3fPlayerPos_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataFloatPlayerDirectionY_d{};
};

}  // namespace uking::action

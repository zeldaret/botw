#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpToGameDataVec3f : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpToGameDataVec3f, ksys::act::ai::Action)
public:
    explicit WarpToGameDataVec3f(const InitArg& arg);
    ~WarpToGameDataVec3f() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    float* mDestinationX_d{};
    // dynamic_param at offset 0x28
    float* mDestinationY_d{};
    // dynamic_param at offset 0x30
    float* mDestinationZ_d{};
    // dynamic_param at offset 0x38
    float* mDirectionY_d{};
    // dynamic_param at offset 0x40
    bool* mRotToVec3f_d{};
    // dynamic_param at offset 0x48
    sead::SafeString mGameDataVec3fWarpToPos_d{};
    // dynamic_param at offset 0x58
    sead::SafeString mGameDataVec3fRotDir_d{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpToActor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpToActor, ksys::act::ai::Action)
public:
    explicit WarpToActor(const InitArg& arg);
    ~WarpToActor() override;

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
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x58
    sead::SafeString mGameDataVec3fRotDir_d{};
};

}  // namespace uking::action

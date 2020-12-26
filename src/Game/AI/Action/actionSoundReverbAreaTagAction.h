#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SoundReverbAreaTagAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(SoundReverbAreaTagAction, AreaTagAction)
public:
    explicit SoundReverbAreaTagAction(const InitArg& arg);
    ~SoundReverbAreaTagAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x70
    const float* mReverbSendAdd_m{};
    // map_unit_param at offset 0x78
    const float* mReverbTimeAdd_m{};
    // map_unit_param at offset 0x80
    const float* mEarlyReflectionFeedbackAdd_m{};
    // map_unit_param at offset 0x88
    const float* mRoomHfAdd_m{};
    // map_unit_param at offset 0x90
    const float* mReverbAdd_m{};
    // map_unit_param at offset 0x98
    const float* mMerginDistance_m{};
};

}  // namespace uking::action

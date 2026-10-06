#pragma once

#include "Game/Actor/Area/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::snd {

class SoundOcclusionTagAction : public uking::action::AreaTagAction {
    SEAD_RTTI_OVERRIDE(SoundOcclusionTagAction, uking::action::AreaTagAction)
public:
    explicit SoundOcclusionTagAction(const InitArg& arg);
    ~SoundOcclusionTagAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const float* mOcclusionLevel_s{};
};

}  // namespace ksys::snd

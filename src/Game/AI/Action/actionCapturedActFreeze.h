#pragma once

#include "Game/AI/Action/actionFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CapturedActFreeze : public Freeze {
    SEAD_RTTI_OVERRIDE(CapturedActFreeze, Freeze)
public:
    explicit CapturedActFreeze(const InitArg& arg);
    ~CapturedActFreeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const float* mPauseDelayFrames_s{};
    // static_param at offset 0x80
    sead::SafeString mASKeyName_s{};
};

}  // namespace uking::action

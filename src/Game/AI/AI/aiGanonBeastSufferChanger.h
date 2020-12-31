#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBeastSufferChanger : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBeastSufferChanger, ksys::act::ai::Ai)
public:
    explicit GanonBeastSufferChanger(const InitArg& arg);
    ~GanonBeastSufferChanger() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    int* mSufferChangeStopCounter_a{};
    // aitree_variable at offset 0x40
    bool* mIsWeakPointAppearMode_a{};
    // aitree_variable at offset 0x48
    bool* mInBeastGanonVoiceSequence_a{};
    // aitree_variable at offset 0x50
    void* mSimpleDialogUnit_a{};
    // static_param at offset 0x58
    const int* mWeakPoint1Time_s{};
    // static_param at offset 0x60
    const int* mWeakPoint2Time_s{};
    // static_param at offset 0x68
    const int* mWeakPoint3Time_s{};
    // static_param at offset 0x70
    const int* mWeakPoint4Time_s{};
    // static_param at offset 0x78
    const int* mCloseOption_s{};
    // static_param at offset 0x80
    const int* mTimer_s{};
    // static_param at offset 0x88
    sead::SafeString mmstxtName_s{};
    // static_param at offset 0x98
    sead::SafeString mlabelName_s{};
    // static_param at offset 0xa8
    sead::SafeString mlabelName2_s{};
    // static_param at offset 0xb8
    sead::SafeString mlabelName3_s{};
};

}  // namespace uking::ai

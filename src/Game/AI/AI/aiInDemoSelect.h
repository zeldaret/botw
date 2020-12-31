#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InDemoSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InDemoSelect, ksys::act::ai::Ai)
public:
    explicit InDemoSelect(const InitArg& arg);
    ~InDemoSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mDemoRetDelayMax_s{};
    // static_param at offset 0x40
    const bool* mOtherDemoNoRun_s{};
    // static_param at offset 0x48
    const bool* mForceChangeDemo_s{};
    // static_param at offset 0x50
    sead::SafeString mDemoFile_s{};
    // static_param at offset 0x60
    sead::SafeString mDemoEntryPoint_s{};
};

}  // namespace uking::ai

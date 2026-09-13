#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MimicryResetCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MimicryResetCheck, ksys::act::ai::Ai)
public:
    explicit MimicryResetCheck(const InitArg& arg);
    ~MimicryResetCheck() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mResetRate_s{};
    // aitree_variable at offset 0x40
    int* mMimicryMaterial_a{};
    // aitree_variable at offset 0x48
    bool* mIsStartResetMimicry_a{};
};

}  // namespace uking::ai

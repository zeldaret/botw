#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NpcTebaRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NpcTebaRoot, ksys::act::ai::Ai)
public:
    explicit NpcTebaRoot(const InitArg& arg);
    ~NpcTebaRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mShowMessageLockonMinInterval_s{};
    // static_param at offset 0x40
    const float* mApproachPlayerHeight_s{};
    // static_param at offset 0x48
    const float* mShowMessageDoDist_s{};
};

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PrevSomeASSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PrevSomeASSelect, ksys::act::ai::Ai)
public:
    explicit PrevSomeASSelect(const InitArg& arg);
    ~PrevSomeASSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mSeqBank_s{};
    // static_param at offset 0x40
    const int* mTargetBone_s{};
};

}  // namespace uking::ai

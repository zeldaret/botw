#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqRandomRepeat : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqRandomRepeat, ksys::act::ai::Ai)
public:
    explicit SeqRandomRepeat(const InitArg& arg);
    ~SeqRandomRepeat() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMinActionNum_s{};
    // static_param at offset 0x40
    const int* mMaxActionNum_s{};
    // static_param at offset 0x48
    const bool* mIsEndChangeable_s{};
};

}  // namespace uking::ai

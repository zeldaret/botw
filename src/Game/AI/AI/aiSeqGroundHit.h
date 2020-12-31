#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqGroundHit : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqGroundHit, ksys::act::ai::Ai)
public:
    explicit SeqGroundHit(const InitArg& arg);
    ~SeqGroundHit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCheckType_s{};
    // static_param at offset 0x40
    const bool* mIsCheckChangeable_s{};
    // static_param at offset 0x48
    const bool* mIsNoHitEnd_s{};
};

}  // namespace uking::ai

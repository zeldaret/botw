#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokPinWheelRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokPinWheelRoot, ksys::act::ai::Ai)
public:
    explicit KorokPinWheelRoot(const InitArg& arg);
    ~KorokPinWheelRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRotSpd_s{};
    // static_param at offset 0x40
    const float* mLength_s{};
};

}  // namespace uking::ai

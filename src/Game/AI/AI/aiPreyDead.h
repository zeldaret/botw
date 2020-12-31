#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PreyDead : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreyDead, ksys::act::ai::Ai)
public:
    explicit PreyDead(const InitArg& arg);
    ~PreyDead() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSendRadius_s{};
    // static_param at offset 0x40
    const bool* mIsEmitForceEscapeSignal_s{};
};

}  // namespace uking::ai

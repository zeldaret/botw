#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HangedLamp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HangedLamp, ksys::act::ai::Ai)
public:
    explicit HangedLamp(const InitArg& arg);
    ~HangedLamp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x28];
    // static_param at offset 0x60
    const bool* mDisableImpulseByArrow_s{};
};

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchElectric : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwitchElectric, ksys::act::ai::Ai)
public:
    explicit SwitchElectric(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mElecReq_s{};
    // static_param at offset 0x40
    const float* mVolReq_s{};
};

}  // namespace uking::ai

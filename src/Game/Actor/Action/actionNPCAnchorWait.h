#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCAnchorWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCAnchorWait, ksys::act::ai::Action)
public:
    explicit NPCAnchorWait(const InitArg& arg);
    ~NPCAnchorWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsRainAnchor_d{};
    // dynamic_param at offset 0x28
    bool* mIsStartSameAS_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mASName_d{};
};

}  // namespace uking::action

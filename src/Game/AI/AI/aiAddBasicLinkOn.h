#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddBasicLinkOn : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AddBasicLinkOn, ksys::act::ai::Ai)
public:
    explicit AddBasicLinkOn(const InitArg& arg);
    ~AddBasicLinkOn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mOnlyOne_s{};
    // static_param at offset 0x40
    const bool* mIsBroadCastOnlyOne_s{};
};

}  // namespace uking::ai

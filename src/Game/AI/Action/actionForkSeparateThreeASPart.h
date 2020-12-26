#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSeparateThreeASPart : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkSeparateThreeASPart, ksys::act::ai::Action)
public:
    explicit ForkSeparateThreeASPart(const InitArg& arg);
    ~ForkSeparateThreeASPart() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mRootNode_s{};
    // static_param at offset 0x30
    sead::SafeString mSlot1StartNode_s{};
    // static_param at offset 0x40
    sead::SafeString mSlot2StartNode_s{};
};

}  // namespace uking::action

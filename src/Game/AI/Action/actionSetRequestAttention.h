#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetRequestAttention : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetRequestAttention, ksys::act::ai::Action)
public:
    explicit SetRequestAttention(const InitArg& arg);
    ~SetRequestAttention() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsOn_s{};
    // static_param at offset 0x28
    const bool* mIsAll_s{};
    // static_param at offset 0x30
    sead::SafeString mAttName_s{};
};

}  // namespace uking::action

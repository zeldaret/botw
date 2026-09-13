#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsFireTailAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsFireTailAttack, ksys::act::ai::Action)
public:
    explicit RemainsFireTailAttack(const InitArg& arg);
    ~RemainsFireTailAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x28
    sead::SafeString mASKeyName_s{};
};

}  // namespace uking::action

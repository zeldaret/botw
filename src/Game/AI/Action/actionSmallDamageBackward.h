#pragma once

#include "Game/AI/Action/actionSmallDamageBackwardBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageBackward : public SmallDamageBackwardBase {
    SEAD_RTTI_OVERRIDE(SmallDamageBackward, SmallDamageBackwardBase)
public:
    explicit SmallDamageBackward(const InitArg& arg);
    ~SmallDamageBackward() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const bool* mIsReStartASByDamage_s{};
    // static_param at offset 0xc8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action

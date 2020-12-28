#pragma once

#include "Game/AI/Action/actionEat.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EatWithAS : public Eat {
    SEAD_RTTI_OVERRIDE(EatWithAS, Eat)
public:
    explicit EatWithAS(const InitArg& arg);
    ~EatWithAS() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action

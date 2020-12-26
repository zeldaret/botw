#pragma once

#include "Game/AI/Action/actionEat.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EatWithAS : public Eat {
    SEAD_RTTI_OVERRIDE(EatWithAS, Eat)
public:
    explicit EatWithAS(const InitArg& arg);
    ~EatWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action

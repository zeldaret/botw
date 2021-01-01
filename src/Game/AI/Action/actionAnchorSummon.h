#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnchorSummon : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(AnchorSummon, ActionWithPosAngReduce)
public:
    explicit AnchorSummon(const InitArg& arg);
    ~AnchorSummon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x40
    sead::SafeString mSummonActor_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mSummonActorEquip1_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mSummonActorEquip2_d{};
};

}  // namespace uking::action

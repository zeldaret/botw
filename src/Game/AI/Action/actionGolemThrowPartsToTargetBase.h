#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GolemThrowPartsToTargetBase : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(GolemThrowPartsToTargetBase, ActionWithAS)
public:
    explicit GolemThrowPartsToTargetBase(const InitArg& arg);
    ~GolemThrowPartsToTargetBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // static_param at offset 0x40
    sead::SafeString mTgtBodyName_s{};
    // static_param at offset 0x50
    sead::SafeString mChmObjectName_s{};
    // aitree_variable at offset 0xe8
    void* mGolemChemicalController_a{};
};

}  // namespace uking::action

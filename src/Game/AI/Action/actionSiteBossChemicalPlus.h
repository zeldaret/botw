#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossChemicalPlus : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(SiteBossChemicalPlus, ActionWithPosAngReduce)
public:
    explicit SiteBossChemicalPlus(const InitArg& arg);
    ~SiteBossChemicalPlus() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const bool* mIsDeleteAllChildDevice_s{};
    // static_param at offset 0x38
    const bool* mIsSetCanGuardArrowFlag_s{};
    // static_param at offset 0x40
    sead::SafeString mChemicalLoopASName_s{};
    // static_param at offset 0x50
    sead::SafeString mChmicalPlusASName_s{};
};

}  // namespace uking::action

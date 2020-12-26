#pragma once

#include "Game/AI/Action/actionSideWalkBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SideWalk : public SideWalkBase {
    SEAD_RTTI_OVERRIDE(SideWalk, SideWalkBase)
public:
    explicit SideWalk(const InitArg& arg);
    ~SideWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe8
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0xf0
    sead::SafeString mASKeyName_s{};
};

}  // namespace uking::action

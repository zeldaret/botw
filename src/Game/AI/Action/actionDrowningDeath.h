#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DrowningDeath : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DrowningDeath, ksys::act::ai::Action)
public:
    explicit DrowningDeath(const InitArg& arg);
    ~DrowningDeath() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mPosBaseRagdollRbName_s{};
};

}  // namespace uking::action

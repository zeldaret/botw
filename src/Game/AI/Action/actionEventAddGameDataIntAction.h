#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventAddGameDataIntAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventAddGameDataIntAction, ksys::act::ai::Action)
public:
    explicit EventAddGameDataIntAction(const InitArg& arg);
    ~EventAddGameDataIntAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsSignInversion_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mGameDataIntDstName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mGameDataIntSrcName_d{};
};

}  // namespace uking::action

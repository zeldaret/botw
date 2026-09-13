#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventAddGameDataToRupeeAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventAddGameDataToRupeeAction, ksys::act::ai::Action)
public:
    explicit EventAddGameDataToRupeeAction(const InitArg& arg);
    ~EventAddGameDataToRupeeAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsSignInversion_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mGameDataIntAddValueName_d{};
};

}  // namespace uking::action

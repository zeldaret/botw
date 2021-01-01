#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventPlayUiScreenAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPlayUiScreenAction, ksys::act::ai::Action)
public:
    explicit EventPlayUiScreenAction(const InitArg& arg);
    ~EventPlayUiScreenAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mClipIndex_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mScreenName_d{};
};

}  // namespace uking::action

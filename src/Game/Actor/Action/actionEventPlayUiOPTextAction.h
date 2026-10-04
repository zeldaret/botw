#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventPlayUiOPTextAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPlayUiOPTextAction, ksys::act::ai::Action)
public:
    explicit EventPlayUiOPTextAction(const InitArg& arg);
    ~EventPlayUiOPTextAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mClipIndex_d{};
    // dynamic_param at offset 0x28
    int* mTextType_d{};
};

}  // namespace uking::action

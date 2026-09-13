#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventPlayUiActorName : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPlayUiActorName, ksys::act::ai::Action)
public:
    explicit EventPlayUiActorName(const InitArg& arg);
    ~EventPlayUiActorName() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mClipIndex_d{};
    // dynamic_param at offset 0x28
    int* mActorType_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mActorName_d{};
};

}  // namespace uking::action

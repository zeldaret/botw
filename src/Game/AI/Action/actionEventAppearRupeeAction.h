#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventAppearRupeeAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventAppearRupeeAction, ksys::act::ai::Action)
public:
    explicit EventAppearRupeeAction(const InitArg& arg);
    ~EventAppearRupeeAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mIsVisible_d{};
};

}  // namespace uking::action

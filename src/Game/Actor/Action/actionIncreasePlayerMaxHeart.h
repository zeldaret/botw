#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IncreasePlayerMaxHeart : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IncreasePlayerMaxHeart, ksys::act::ai::Action)
public:
    explicit IncreasePlayerMaxHeart(const InitArg& arg);
    ~IncreasePlayerMaxHeart() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mValue_d{};
    // dynamic_param at offset 0x28
    bool* mIsMoveCenter_d{};
};

}  // namespace uking::action

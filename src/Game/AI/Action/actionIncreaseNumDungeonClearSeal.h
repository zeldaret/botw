#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IncreaseNumDungeonClearSeal : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IncreaseNumDungeonClearSeal, ksys::act::ai::Action)
public:
    explicit IncreaseNumDungeonClearSeal(const InitArg& arg);
    ~IncreaseNumDungeonClearSeal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mActorName_s{};
    // dynamic_param at offset 0x30
    int* mValue_d{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AddAutoPlacementCreator : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AddAutoPlacementCreator, ksys::act::ai::Action)
public:
    explicit AddAutoPlacementCreator(const InitArg& arg);
    ~AddAutoPlacementCreator() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mCount_m{};
    // map_unit_param at offset 0x28
    sead::SafeString mActorName_m{};
    // map_unit_param at offset 0x38
    sead::SafeString mShape_m{};
};

}  // namespace uking::action

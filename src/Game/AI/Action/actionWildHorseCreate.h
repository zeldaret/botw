#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WildHorseCreate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WildHorseCreate, ksys::act::ai::Action)
public:
    explicit WildHorseCreate(const InitArg& arg);
    ~WildHorseCreate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mMinCreateNum_s{};
    // static_param at offset 0x28
    const int* mMaxCreateNum_s{};
    // map_unit_param at offset 0x30
    const int* mWildHorseCreateNum_m{};
};

}  // namespace uking::action

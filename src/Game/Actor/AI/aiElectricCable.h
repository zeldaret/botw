#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ElectricCable : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ElectricCable, ksys::act::ai::Ai)
public:
    explicit ElectricCable(const InitArg& arg);
    ~ElectricCable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsDisplayOnUI_m{};
};

}  // namespace uking::ai

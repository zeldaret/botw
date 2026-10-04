#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetPaletteType : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetPaletteType, ksys::act::ai::Action)
public:
    explicit EventSetPaletteType(const InitArg& arg);
    ~EventSetPaletteType() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mPaletteType_d{};
    // dynamic_param at offset 0x28
    int* mChangeFrame_d{};
    // dynamic_param at offset 0x30
    int* mEndFrame_d{};
    // dynamic_param at offset 0x38
    float* mSpeed_d{};
};

}  // namespace uking::action

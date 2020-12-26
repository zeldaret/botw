#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetSkyPaletteType : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetSkyPaletteType, ksys::act::ai::Action)
public:
    explicit EventSetSkyPaletteType(const InitArg& arg);
    ~EventSetSkyPaletteType() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mSkyPalette_d{};
};

}  // namespace uking::action

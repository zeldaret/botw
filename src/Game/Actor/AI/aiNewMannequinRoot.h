#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NewMannequinRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NewMannequinRoot, ksys::act::ai::Ai)
public:
    explicit NewMannequinRoot(const InitArg& arg);
    ~NewMannequinRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mArmorDyeColor_m{};
    // map_unit_param at offset 0x40
    const int* mShopSellType_m{};
};

}  // namespace uking::ai

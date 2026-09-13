#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NearCreateAppearTypeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NearCreateAppearTypeSelect, ksys::act::ai::Ai)
public:
    explicit NearCreateAppearTypeSelect(const InitArg& arg);
    ~NearCreateAppearTypeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mNearCreateAppearType_m{};
};

}  // namespace uking::ai
